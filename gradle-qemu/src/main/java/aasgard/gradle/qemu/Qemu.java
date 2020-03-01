package aasgard.gradle.qemu;

import static java.util.Arrays.asList;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.gradle.api.Action;
import org.gradle.api.provider.Provider;

public final class Qemu 
{
	public static Process system (QemuSystemSpec spec) throws IOException
	{
		final var command = new ArrayList<String>();
		command.add(spec.getArchitecture().map(it -> "qemu-system-" + it).get());
		ifPresent(spec.getBios(), it -> addAll(command, "-bios", it.getAsFile().toString()));
		ifPresent(spec.getCdrom(), it -> addAll(command, "-cdrom", it.getAsFile().toString()));
		ifPresent(spec.getGdb(), it -> addAll(command, "-gdb", it));
		ifPresent(spec.getDisplay(), it -> addAll(command, "-display", it));
		ifPresent(spec.getKernel(), it -> addAll(command, "-kernel", it.getAsFile().toString()));
		ifPresent(spec.getProcessor(), it -> addAll(command, "-cpu", it));
		addAll(command, "-net", "none");
		if (! spec.getStart().get()) { command.add("-S"); }
		
		final var err = spec.getTemporaryDir().file("err.txt");
		final var out = spec.getTemporaryDir().file("out.txt");
		
		final var builder = new ProcessBuilder(command);
		final var environment = builder.environment();
		spec.getEnvironment().get().forEach((key, value) -> environment.put(key, value));
		builder.redirectError(err.get().getAsFile());
		builder.redirectOutput(out.get().getAsFile());
		return builder.start();
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
