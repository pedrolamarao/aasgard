package aasgard.gradle.gdb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

import org.antlr.v4.runtime.ANTLRErrorListener;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

import aasgard.gdb.GdbMiLexer;
import aasgard.gdb.GdbMiParser;
import aasgard.gdb.GdbMiParser.OutputContext;

public final class GdbMiParserQueue 
{
	public static final OutputContext END = new OutputContext(null, -1);
	
	private final ArrayBlockingQueue<OutputContext> queue;
	
	private final Thread thread;
	
	public GdbMiParserQueue (int capacity, InputStream stream, ANTLRErrorListener... errors)
	{
		queue = new ArrayBlockingQueue<>(capacity);
		thread = new Thread(() -> parse(stream, errors));
		thread.start();
	}
	
	public OutputContext poll (int time, TimeUnit unit) throws InterruptedException
	{
		return queue.poll(time, unit);
	}
	
	public void join (int time) throws InterruptedException
	{
		thread.join(time);
	}
	
	public void parse (InputStream stream, ANTLRErrorListener... errors)
	{
		try (var reader = new BufferedReader(new InputStreamReader(stream)))
		{
			outer:
			while (true)
			{
				var builder = new StringBuilder();
				
				inner:
				while (true)
				{
					var line = reader.readLine();
					if (line == null) { queue.put(END); break outer; }
					builder.append(line).append('\n');
					if ("(gdb) ".equals(line)) { break inner; }
				}
				
				var lexer = new GdbMiLexer(CharStreams.fromString(builder.toString()));
				for (var error : errors) lexer.addErrorListener(error);
				
				var parser = new GdbMiParser(new CommonTokenStream(lexer));
				for (var error : errors) parser.addErrorListener(error);
				
				queue.put(parser.output());
			}
		} 
		catch (IOException | InterruptedException e)
		{
			queue.offer(END);
			e.printStackTrace();
		}
	}
}
