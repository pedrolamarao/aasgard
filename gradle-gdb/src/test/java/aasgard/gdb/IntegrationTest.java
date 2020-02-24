package aasgard.gdb;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNotSame;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.Test;

import aasgard.gradle.gdb.GdbMiParserQueue;
import aasgard.gradle.gdb.GdbMiProcess;

public class IntegrationTest 
{
	public static final int timeout = 1000;
	
	@Test
	public void commands () throws IOException, InterruptedException
	{
		var builder = new ProcessBuilder("gdb", "--interpreter=mi");
		var error = new ErrorListener();
		var process = new GdbMiProcess(builder.start(), error);
		
		var output = process.poll(timeout, TimeUnit.MILLISECONDS);
		assertFalse(error.get());
		assertNotNull(output);
		assertNotSame(output, GdbMiParserQueue.END);

		process.push("help");

		output = process.poll(timeout, TimeUnit.MILLISECONDS);
		assertFalse(error.get());
		assertNotNull(output);	
		assertNotSame(output, GdbMiParserQueue.END);

		process.push("quit");

		output = process.poll(timeout, TimeUnit.MILLISECONDS);
		assertFalse(error.get());
		assertNotNull(output);	
		assertSame(output, GdbMiParserQueue.END);

		assertTrue(process.waitFor(timeout, TimeUnit.MILLISECONDS));
	}
}
