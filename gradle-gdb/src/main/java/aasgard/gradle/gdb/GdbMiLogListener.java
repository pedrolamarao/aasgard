package aasgard.gradle.gdb;

import java.io.IOException;
import java.io.Writer;

import aasgard.gdb.GdbMiBaseListener;
import aasgard.gdb.GdbMiParser;

public final class GdbMiLogListener extends GdbMiBaseListener
{
	private final Writer writer;
	
	public GdbMiLogListener (Writer writer)
	{
		this.writer = writer;
		Runtime.getRuntime().addShutdownHook(new Thread(() -> { try { writer.close(); } catch (IOException e) {} }));
	}
	
	@Override 
	public void exitOutput (GdbMiParser.OutputContext ctx) 
	{
		try 
		{
			writer.append(ctx.getText()).flush();
		} 
		catch (IOException e) 
		{
			throw new RuntimeException(e);
		}
	}
}
