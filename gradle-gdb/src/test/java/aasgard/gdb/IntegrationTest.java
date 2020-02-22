package aasgard.gdb;

import static java.lang.System.err;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

import org.antlr.v4.runtime.CommonToken;
import org.antlr.v4.runtime.CommonTokenFactory;
import org.antlr.v4.runtime.UnbufferedCharStream;
import org.antlr.v4.runtime.UnbufferedTokenStream;
import org.junit.jupiter.api.Test;

import aasgard.gdb.GdbMiParser.OutputContext;

public class IntegrationTest 
{
	static final class ParserQueue
	{
		private final ArrayBlockingQueue<OutputContext> queue = new ArrayBlockingQueue<>(16);
		
		private final Thread thread;
		
		public ParserQueue (InputStream stream, ErrorListener error) throws IOException
		{
			thread = new Thread(() -> {
				try 
				{
					var lexer = new GdbMiLexer(new UnbufferedCharStream(stream));
			        lexer.setTokenFactory(new CommonTokenFactory(true));
					lexer.addErrorListener(error);

					err.println("lexer");

					var parser = new GdbMiParser(new UnbufferedTokenStream<CommonToken>(lexer));
					parser.addErrorListener(error);

					err.println("parser");
					
					while (true) {
						var output = parser.output();
						err.println(output);
						queue.put(output);
					}
				}
				catch (InterruptedException e) 
				{
					e.printStackTrace(err);
				}
			});
			thread.start();
			err.println("started");
		}
		
		public OutputContext poll (long time, TimeUnit unit) throws InterruptedException
		{
			return queue.poll(time, unit);
		}
		
		public void join (int milliseconds) throws InterruptedException
		{
			thread.join(milliseconds);
		}
	}

	@Test
	public void parser () throws IOException, InterruptedException
	{
		var builder = new ProcessBuilder("gdb", "--interpreter=mi");
		var process = builder.start();

		var error = new ErrorListener();
		var in = new ParserQueue(process.getInputStream(), error);
		
		try (var writer = new OutputStreamWriter(process.getOutputStream())) 
		{
			var output = in.poll(10000, TimeUnit.MILLISECONDS);
			assertNotNull(output);
			assertFalse(error.get());

			writer.append("quit\n");

			output = in.poll(10000, TimeUnit.MILLISECONDS);
			assertNotNull(output);	
			assertFalse(error.get());
		}

		assertTrue(process.waitFor(1000, TimeUnit.MILLISECONDS));
		
		process.destroyForcibly();
		in.join(500);
	}
}
