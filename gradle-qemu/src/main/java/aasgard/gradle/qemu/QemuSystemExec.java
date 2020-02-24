package aasgard.gradle.qemu;

import java.io.IOException;

import javax.inject.Inject;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.model.ObjectFactory;
import org.gradle.api.provider.MapProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFile;
import org.gradle.api.tasks.Optional;
import org.gradle.api.tasks.TaskAction;

public abstract class QemuSystemExec extends DefaultTask
{
	private final QemuSystemSpec spec;
	
	// life
	
	@Inject
	public QemuSystemExec (ObjectFactory objects)
	{
		this.spec = objects.newInstance(QemuSystemSpec.class);
	}
	
	// properties
	
	@Input
	public Property<String> getArchitecture () { return spec.getArchitecture(); }
	
	@Optional
	@InputFile
	public RegularFileProperty getBios () { return spec.getBios(); }
	
	@Optional
	@InputFile
	public RegularFileProperty getCdrom () { return spec.getCdrom(); }

	@Input
	public MapProperty<String, String> getEnvironment () { return spec.getEnvironment(); }
	
	@Optional
	@Input
	public Property<String> getGdb () { return spec.getGdb(); }
	
	@Optional
	@InputFile
	public RegularFileProperty getKernel () { return spec.getKernel(); }
	
	@Optional
	@Input
	public Property<String> getProcessor () { return spec.getProcessor(); }
	
	@Input
	public Property<Boolean> getStart () { return spec.getStart(); }
	
	// task
	
	@TaskAction
	public void action () throws IOException
	{
		Qemu.system(spec);
	}
}
