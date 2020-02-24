package aasgard.gradle.gdb;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.concurrent.TimeUnit;

import org.antlr.v4.runtime.ANTLRErrorListener;

import aasgard.gdb.GdbMiParser.OutputContext;

public final class GdbMiProcess 
{
	private final Writer assembler;
	
	private final GdbMiParserQueue parser;
	
	private final Process process;
	
	public GdbMiProcess (Process process, ANTLRErrorListener... errors)
	{
		this.assembler = new OutputStreamWriter(process.getOutputStream());
		this.parser = new GdbMiParserQueue(16, process.getInputStream(), errors);
		this.process = process;
	}
	
	public OutputContext poll (int time, TimeUnit unit) throws InterruptedException
	{
		return parser.poll(time, unit);
	}
	
	public OutputContext poll (int time) throws InterruptedException
	{
		return parser.poll(time, TimeUnit.MILLISECONDS);
	}
	
	public void push (String request) throws IOException
	{
		assembler.append(request).append('\n').flush();
	}
	
	public boolean waitFor (int time, TimeUnit unit) throws InterruptedException
	{
		return process.waitFor(time, unit);
	}
	
	public boolean waitFor (int time) throws InterruptedException
	{
		return process.waitFor(time, TimeUnit.MILLISECONDS);
	}
}
