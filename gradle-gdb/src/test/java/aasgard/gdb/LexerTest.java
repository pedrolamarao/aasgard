package aasgard.gdb;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.params.provider.Arguments.arguments;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

import org.antlr.v4.runtime.CharStreams;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class LexerTest 
{
	public static Stream<Arguments> resources ()
	{
		return Stream.of(
			arguments("banner", Arrays.asList(
				"=", "thread-group-added", ",",
					"id", "=", "\"i1\"",
				"~", "\"GNU gdb (GDB) 9.1\\n\"",
				"~", "\"Copyright (C) 2020 Free Software Foundation, Inc.\\n\"",
				"~", "\"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\\nThis is free software: you are free to change and redistribute it.\\nThere is NO WARRANTY, to the extent permitted by law.\"",
				"~", "\"\\nType \\\"show copying\\\" and \\\"show warranty\\\" for details.\\n\"",
				"~", "\"This GDB was configured as \\\"--host=x86_64-pc-linux-gnu --target=i686-pc-elf\\\".\\n\"",
				"~", "\"Type \\\"show configuration\\\" for configuration details.\\n\"",
				"~", "\"For bug reporting instructions, please see:\\n\"",
				"~", "\"<http://www.gnu.org/software/gdb/bugs/>.\\n\"",
				"~", "\"Find the GDB manual and other documentation resources online at:\\n    <http://www.gnu.org/software/gdb/documentation/>.\"",
				"~", "\"\\n\\n\"",
				"~", "\"For help, type \\\"help\\\".\\n\"",
				"~", "\"Type \\\"apropos word\\\" to search for commands related to \\\"word\\\".\\n\"",
				"(gdb) "
			)),
			arguments("file", Arrays.asList(
				"&", "\"file test-multiboot2-ia32-start/build/exe/main/debug/test-multiboot2-ia32-start\\n\"",
				"~", "\"Reading symbols from test-multiboot2-ia32-start/build/exe/main/debug/test-multiboot2-ia32-start...\\n\"",
				"^", "done",
				"(gdb) "
			)),
			arguments("file_error", Arrays.asList(
				"&", "\"file buexe/main/debug/test-multiboot2-ia32-start\\n\"",
				"&", "\"buexe/main/debug/test-multiboot2-ia32-start: No such file or directory.\\n\"",
				"^", "error", ",", 
					"msg", "=", "\"buexe/main/debug/test-multiboot2-ia32-start: No such file or directory.\"",
				"(gdb) "
			)),
			arguments("kill", Arrays.asList(
				"=", "thread-group-exited", ",", "id", "=" ,"\"i1\"",
				"~", "\"[Inferior 1 (Remote target) killed]\\n\"",
				"^", "done",
				"(gdb) "
			)),
			arguments("target_remote", Arrays.asList(
				"&", "\"target remote localhost:1234\\n\"",
				"~", "\"Remote debugging using localhost:1234\\n\"",
				"=", "thread-group-started", ",", 
					"id", "=", "\"i1\"", ",", 
					"pid", "=", "\"42000\"",
				"=", "thread-created", ",", 
 					"id", "=", "\"1\"", ",", 
					"group-id", "=", "\"i1\"",
				"~", "\"0x0000fff0 in ?? ()\\n\"",
				"*", "stopped", ",", 
					"frame", "=", "{", 
						"addr", "=", "\"0x0000fff0\"", ",", 
						"func", "=", "\"??\"", ",", 
						"args", "=", "[", "]", ",",
						"arch", "=", "\"i386\"",
					"}", ",",
					"thread-id", "=", "\"1\"", ",",
					"stopped-threads", "=", "\"all\"",
				"^", "done",
				"(gdb) "
			)),
			arguments("target_remote_warning", Arrays.asList(
				"&", "\"target remote localhost:1234\\n\"",
				"~", "\"Remote debugging using localhost:1234\\n\"",
				"=", "thread-group-started", ",", 
					"id", "=", "\"i1\"", ",", 
					"pid", "=", "\"42000\"",
				"&", "\"warning: No executable has been specified and target does not support\\ndetermining executable automatically.  Try using the \\\"file\\\" command.\"",
				"&", "\"\\n\"",
				"=", "thread-created", ",", 
					"id", "=", "\"1\"", ",", 
					"group-id", "=", "\"i1\"",
				"~", "\"0x0000fff0 in ?? ()\\n\"",
				"*", "stopped", ",", 
					"frame", "=", "{", 
						"addr", "=", "\"0x0000fff0\"", ",", 
						"func", "=", "\"??\"", ",", 
						"args", "=", "[", "]", ",",
						"arch", "=", "\"i386\"",
					"}", ",",
					"thread-id", "=", "\"1\"", ",",
					"stopped-threads", "=", "\"all\"",
				"^", "done",
				"(gdb) "
			)),
			arguments("thbreak", Arrays.asList(
				"~", "\"Hardware assisted breakpoint 1 at 0x105f\\n\"",
				"=", "breakpoint-created", ",", 
					"bkpt", "=", "{",
						"number", "=", "\"1\"", ",",
						"type", "=", "\"hw breakpoint\"", ",",
						"disp", "=", "\"del\"", ",",
						"enabled", "=", "\"y\"", ",",
						"addr", "=", "\"0x0000105f\"", ",",
						"at", "=", "\"<_start>\"", ",",
						"thread-groups", "=", "[", "\"i1\"", "]", ",",
						"times", "=", "\"0\"", ",",
						"original-location", "=", "\"_start\"", 
					"}",
				"^", "done",
				"(gdb) "
			))
		);
	}
	
	@ParameterizedTest
	@MethodSource("resources")
	public void lex (String resource, List<String> expected) throws IOException
	{
		var error = new ErrorListener();
		
		try (var stream = getClass().getResourceAsStream(resource))
		{
			var lexer = new GdbMiLexer(CharStreams.fromStream(stream));
			lexer.addErrorListener(error);
			
			for (String s : expected) 
			{
				error.clear();
				var token = lexer.nextToken();
				while (token.getType() == GdbMiLexer.NL) token = lexer.nextToken();
				assertFalse(error.get());
				assertEquals(s, token.getText(), "token: " + token);
			}
		}
	}
}
