package aasgard.gradle.qemu;

import static java.util.Arrays.asList;

import java.io.IOException;
import java.util.ArrayList;

import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.Property;
import org.gradle.api.tasks.Input;
import org.gradle.api.tasks.InputFile;
import org.gradle.api.tasks.Optional;
import org.gradle.api.tasks.TaskAction;

public abstract class QemuExec extends DefaultTask
{
	// properties
	
	@Input
	public abstract Property<String> getSystem ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getBios ();
	
	@Input
	public abstract Property<String> getGdb ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getKernel ();
	
	@Optional
	@InputFile
	public abstract RegularFileProperty getCdrom ();
	
	@Input
	public abstract Property<Boolean> getStart ();
	
	// life
	
	public QemuExec ()
	{
		getStart().convention(true);
	}
	
	// accessors
	
	public void system (String value)
	{
		getSystem().set(value);
	}
	
	public void bios (RegularFileProperty value)
	{
		getBios().set(value);
	}
	
	public void cdrom (RegularFileProperty value)
	{
		getCdrom().set(value);
	}
	
	public void gdb (String value)
	{
		getGdb().set(value);
	}
	
	public void kernel (RegularFileProperty value)
	{
		getKernel().set(value);		
	}
	
	public void start (boolean value)
	{
		getStart().set(value);
	}
	
	// task
	
	@TaskAction
	public void action () throws IOException
	{
		var command = new ArrayList<String>();
		command.add(getSystem().map(it -> "qemu-system-" + it).get());
		if (getBios().isPresent()) { command.addAll( asList("-bios", getBios().get().getAsFile().toString()) ); }
		if (getKernel().isPresent()) { command.addAll( asList("-kernel", getKernel().get().getAsFile().toString()) ); }
		if (getCdrom().isPresent()) { command.addAll( asList("-cdrom", getCdrom().get().getAsFile().toString()) ); }
		if (getGdb().isPresent()) { command.addAll( asList("-gdb", getGdb().get()) ); }
		if (! getStart().get()) { command.add("-S"); }
		var builder = new ProcessBuilder(command);
		builder.start();
	}
}
