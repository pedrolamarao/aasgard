package aasgard.gradle.gdb;

import java.io.IOException;

import javax.inject.Inject;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.model.ObjectFactory;
import org.gradle.api.provider.MapProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFile;
import org.gradle.api.tasks.TaskAction;

import groovy.lang.Closure;


public abstract class GdbExec extends DefaultTask
{
	private final GdbSpec spec;
	
	// life
	
	@Inject
	public GdbExec (ObjectFactory objects)
	{		
		this.spec = objects.newInstance(GdbSpec.class);
	}
	
	// properties
	
	@Input
	public MapProperty<String, String> getEnvironment () { return spec.getEnvironment(); }
	
	@Input
	public Property<String> getExecutable () { return spec.getExecutable(); }
	
	@InputFile
	public RegularFileProperty getTarget () { return spec.getTarget(); }
	
	@Input
	public Property<Closure<GdbMiProcess>> getScript () { return spec.getScript(); }
	
	// task
	
	@TaskAction
	public void action () throws IOException
	{
		Gdb.exec(spec);
	}
}
