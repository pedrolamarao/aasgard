package aasgard.gdb;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.params.provider.Arguments.arguments;

import java.io.IOException;
import java.util.stream.Stream;

import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

public class ParserTest 
{
	public static Stream<Arguments> resources ()
	{
		return Stream.of(
			arguments("banner"),
			arguments("file"),
			arguments("file_error"),
			arguments("kill"),
			arguments("target_remote"),
			arguments("target_remote_warning"),
			arguments("thbreak")
		);
	}

	@ParameterizedTest
	@MethodSource("resources")
	public void parse (String resource) throws IOException
	{
		final var error = new ErrorListener();
		
		try (var stream = getClass().getResourceAsStream(resource))
		{
			var lexer = new GdbMiLexer(CharStreams.fromStream(stream));
			lexer.addErrorListener(error);
			
			var parser = new GdbMiParser(new CommonTokenStream(lexer));
			parser.addErrorListener(error);

			parser.output();
			assertFalse(error.get());
		}
	}
}
