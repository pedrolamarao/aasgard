package aasgard.gradle.grub;

import static java.lang.String.format;
import static java.lang.String.join;
import static java.nio.charset.StandardCharsets.US_ASCII;
import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.TRUNCATE_EXISTING;
import static java.nio.file.StandardOpenOption.WRITE;

import java.io.File;
import java.io.IOException;
import java.io.Writer;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.ListProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFile;
import org.gradle.api.tasks.OutputFile;
import org.gradle.api.tasks.TaskAction;
import org.gradle.language.cpp.CppExecutable;

public abstract class GrubRescueCompile extends DefaultTask
{
	public abstract Property<CppExecutable> getExecutable ();
	
	@Input
	public abstract ListProperty<String> getFonts ();

	@Input
	public abstract ListProperty<String> getInstall ();

	@Input
	public abstract ListProperty<String> getLoad ();
	
	@Input
	public abstract ListProperty<String> getLocales ();
	
	@InputFile
	public abstract RegularFileProperty getSource ();
	
	@Input
	public abstract ListProperty<String> getThemes ();
	
	@OutputFile
	public abstract RegularFileProperty getTarget ();
	
	public GrubRescueCompile ()
	{
		final var project = getProject();
		final var layout = project.getLayout();
		final var build = layout.getBuildDirectory();
		final var source = getExecutable().flatMap(binary -> binary.getLinkTask().flatMap(link -> link.getLinkedFile()));
		getSource().set(source);
		final var target = getExecutable().flatMap(s -> build.file("grub/bin/" + s.getName() + "/rescue/image"));
		getTarget().set(target);
	}
	
	public void install (String... value)
	{
		getInstall().addAll(value);
	}
	
	public void load (String... value)
	{
		getLoad().addAll(value);
	}
	
	public void executable (CppExecutable value)
	{
		getExecutable().set(value);
	}
	
	private static final String template = 
		"default=0\r\n" + 
		"timeout=0\r\n" + 
		"\r\n" + 
		"menuentry aasgard {\r\n" + 
		"   multiboot2 (cd)/%s\r\n" + 
		"}\r\n";
	
	@TaskAction
	public void action ()
	{
		final var project = getProject();
		final var layout = project.getLayout();
		final var build = layout.getBuildDirectory();
		
		var executableName = getExecutable().get().getName();
		var executableFile = getExecutable().get().getLinkTask().get().getLinkedFile();
		
		var fs = build.dir("grub/fs/" + executableName + "/rescue");
		var cfg = build.file("grub/fs/" + executableName + "/rescue/boot/grub/grub.cfg");
		
		// Create GRUB configuration
		
		project.mkdir(cfg.get().getAsFile().getParentFile());
		try (FileChannel file = FileChannel.open(cfg.get().getAsFile().toPath(), CREATE, TRUNCATE_EXISTING, WRITE);
			 Writer writer = Channels.newWriter(file, US_ASCII))
		{
			writer.append(format(template, executableFile.get().getAsFile().getName()));
		} 
		catch (IOException e) 
		{
			throw new RuntimeException(e);
		}
		
		// Compile GRUB rescue image
		
		project.mkdir(getTarget().getAsFile().map(File::getParentFile));
		project.exec(e -> {
			e.executable("env"); // XXX: I have no idea why my setup fails without this.
			e.args("grub-mkrescue");
            e.args("-o", getTarget().get());
            e.args("--fonts=" + join(" ", getFonts().get()));
            if (! getInstall().get().isEmpty()) { e.args("--install-modules=" + join(" ", getInstall().get())); }
            if (! getLoad().get().isEmpty()) { e.args("--modules=" + join(" ", getLoad().get())); }
            e.args("--locales=" + join(" ", getLocales().get())); 
            e.args("--themes=" + join(" ", getThemes().get())); 
            e.args(getSource().getAsFile().get());
            e.args(fs.get().getAsFile());
		});
	}
}
