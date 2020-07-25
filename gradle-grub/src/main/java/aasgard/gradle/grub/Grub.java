package aasgard.gradle.grub;

import static java.lang.String.join;
import static java.nio.charset.StandardCharsets.US_ASCII;
import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.TRUNCATE_EXISTING;
import static java.nio.file.StandardOpenOption.WRITE;

import java.io.IOException;
import java.io.Writer;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Consumer;

import org.gradle.api.file.Directory;
import org.gradle.api.logging.Logger;
import org.gradle.api.logging.Logging;
import org.gradle.api.provider.ListProperty;
import org.gradle.api.provider.Provider;

public final class Grub 
{
	private static final Logger logger = Logging.getLogger(Grub.class);
	
	private static final String cdrom_cfg = 
		"default=0\r\n" + 
		"timeout=0\r\n" + 
		"\r\n" + 
		"menuentry aasgard {\r\n" + 
		"   multiboot2 (cd)/program\r\n" + 
		"}\r\n";

	public static Process rescue (GrubSpec spec) throws IOException
	{
		Directory tmp = spec.getTemporary().get();
		
		Path cfg = tmp.file("grub.cfg").getAsFile().toPath();
		try (FileChannel file = FileChannel.open(cfg, CREATE, TRUNCATE_EXISTING, WRITE);
			 Writer writer = Channels.newWriter(file, US_ASCII))
		{
			writer.append(cdrom_cfg);
		}
		
		ArrayList<String> command = new ArrayList<>();
		if (spec.getTool().isPresent())
			command.add(spec.getTool().get());
		else
			command.add("grub-mkrescue");	
		add(command, "-o", "" + spec.getTarget().get());
        ifNotEmpty(spec.getInstall(), x -> add(command, "--install-modules=" + join(" ", x)));
        ifNotEmpty(spec.getLoad(), x -> add(command, "--modules=" + join(" ", x)));
		command.add("--fonts=" + join(" ", spec.getFonts().get()));
        command.add("--locales=" + join(" ", spec.getLocales().get())); 
        command.add("--themes=" + join(" ", spec.getThemes().get())); 
        command.add("/boot/grub/grub.cfg=" + cfg);
        command.add(spec.getSource().map(f -> "/program=" + f.getAsFile()).get());
        
        logger.info("GRUB rescue command: {}", join(" ", command));
                
        ProcessBuilder builder = new ProcessBuilder();
        builder.command(command);
        builder.redirectError(tmp.file("err.txt").getAsFile());
        builder.redirectOutput(tmp.file("out.txt").getAsFile());

        return builder.start();
	}

	private static final String memdisk_cfg = 
		"default=0\r\n" + 
		"timeout=0\r\n" + 
		"\r\n" + 
		"menuentry aasgard {\r\n" + 
		"   multiboot2 (memdisk)/program\r\n" + 
		"}\r\n";

	public static Process standalone (GrubSpec spec) throws IOException
	{
		Directory tmp = spec.getTemporary().get();
		
		Path cfg = tmp.file("grub.cfg").getAsFile().toPath();
		try (FileChannel file = FileChannel.open(cfg, CREATE, TRUNCATE_EXISTING, WRITE);
			 Writer writer = Channels.newWriter(file, US_ASCII))
		{
			writer.append(memdisk_cfg);
		}
		
		ArrayList<String> command = new ArrayList<>();
		command.add("grub-mkstandalone");
		add(command, "-O", spec.getFormat().get());
		add(command, "-o", "" + spec.getTarget().get());
		command.add("--fonts=" + join(" ", spec.getFonts().get()));
        ifNotEmpty(spec.getInstall(), x -> add(command, "--install-modules=" + join(" ", x)));
        ifNotEmpty(spec.getLoad(), x -> add(command, "--modules=" + join(" ", x)));
        command.add("--locales=" + join(" ", spec.getLocales().get())); 
        command.add("--themes=" + join(" ", spec.getThemes().get())); 
        command.add("/boot/grub/grub.cfg=" + cfg);
        command.add(spec.getSource().map(f -> "/program=" + f.getAsFile()).get());
        
        logger.info("GRUB standalone command: {}", join(" ", command));

        ProcessBuilder builder = new ProcessBuilder();
        builder.command(command);
        builder.redirectError(tmp.file("err.txt").getAsFile());
        builder.redirectOutput(tmp.file("out.txt").getAsFile());
        
        return builder.start();
	}
	
	public static void add (List<String> list, String... values)
	{
		list.addAll(Arrays.asList(values));
	}
	
	public static <T> void ifNotEmpty (ListProperty<T> provider, Consumer<List<T>> consumer)
	{
		if (! provider.get().isEmpty()) { consumer.accept(provider.get()); }
	}
	
	public static <T> void ifPresent (Provider<T> provider, Consumer<T> consumer)
	{
		if (provider.isPresent()) { consumer.accept(provider.get()); }
	}
}
