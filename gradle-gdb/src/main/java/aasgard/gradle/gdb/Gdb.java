package aasgard.gradle.gdb;

import static java.util.Arrays.asList;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.gradle.api.Action;
import org.gradle.api.provider.Provider;

public final class Gdb 
{
	public static void exec (GdbSpec spec) throws IOException
	{
		final var command = new ArrayList<String>();
		addAll(command, spec.getExecutable().get(), "--nx", "--interpreter=mi");
		ifPresent(spec.getTarget(), it -> addAll(command, "--se", it.toString()));

		final var builder = new ProcessBuilder(command);
		spec.getEnvironment().get().forEach((key, value) -> builder.environment().put(key, value));

		final var gdb = new GdbMiProcess(builder.start());
		spec.getScript().get().execute(gdb);
	}
	
	public static void addAll (List<String> list, String... values)
	{
		list.addAll(asList(values));
	}
	
	public static <T> void ifPresent (Provider<T> provider, Action<? super T> action)
	{
		if (provider.isPresent()) action.execute(provider.get());
	}
}
