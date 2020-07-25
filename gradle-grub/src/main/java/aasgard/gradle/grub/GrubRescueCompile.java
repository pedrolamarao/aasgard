package aasgard.gradle.grub;

import java.io.IOException;

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
	private final GrubSpec spec;
	
	// life
	
	public GrubRescueCompile ()
	{
		final var project = getProject();
		this.spec = project.getObjects().newInstance(GrubSpec.class);
		spec.getTemporary().set(getTemporaryDir());
	}

	// properties
	
	@Input
	public ListProperty<String> getFonts () { return spec.getFonts(); }

	@Input
	public ListProperty<String> getInstall () { return spec.getInstall(); }

	@Input
	public ListProperty<String> getLoad () { return spec.getLoad(); }
	
	@Input
	public ListProperty<String> getLocales () { return spec.getLocales(); }
	
	@Input
	public Property<String> getTool () { return spec.getTool(); }
	
	@InputFile
	public RegularFileProperty getSource () { return spec.getSource(); }
	
	@Input
	public ListProperty<String> getThemes () { return spec.getThemes(); }
	
	@OutputFile
	public RegularFileProperty getTarget () { return spec.getTarget(); }
	
	// utilities
	
	public void executable (CppExecutable source)
	{
		final var file = source.getExecutableFile();
		spec.getSource().set(file);
		spec.getTarget().set(
			file.flatMap(f -> getProject().getLayout().getBuildDirectory().file("grub/bin/" + f.getAsFile() + "/rescue/image"))
		);		
	}
	
	// action
	
	@TaskAction
	public void action () throws IOException, InterruptedException
	{
		int status = Grub.rescue(spec).waitFor();
		if (status != 0) { throw new RuntimeException("task failed with status " + status); }
	}
}
