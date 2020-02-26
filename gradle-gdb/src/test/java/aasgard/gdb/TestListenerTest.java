package aasgard.gdb;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.TimeUnit;

import org.antlr.v4.runtime.tree.ParseTreeWalker;
import org.junit.jupiter.api.Test;

import aasgard.gradle.gdb.GdbMiParserQueue;
import aasgard.gradle.gdb.GdbMiTestListener;

public class TestListenerTest 
{
	@Test
	public void foo () throws IOException, InterruptedException
	{
		final var listener = new GdbMiTestListener("_test_result");

		try (InputStream stream = getClass().getResourceAsStream("foo"))
		{
			final var parser = new GdbMiParserQueue(16, stream);
			while (true)
			{
				final var output = parser.poll(Integer.MAX_VALUE, TimeUnit.MILLISECONDS);
				if (output == GdbMiParserQueue.END) break;
				ParseTreeWalker walker = new ParseTreeWalker();
				walker.walk(listener, output);
			}
		}
		
		assertEquals(0, listener.getValue());
	}
}
