package aasgard.gradle.gdb;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.nio.file.Files;

import javax.inject.Inject;

import org.gradle.api.Action;
import org.gradle.api.model.ObjectFactory;
import org.gradle.api.tasks.TaskContainer;
import org.gradle.api.tasks.TaskProvider;

public abstract class GdbExtension 
{
	@Inject
	public abstract ObjectFactory getObjects ();

	@Inject
	public abstract TaskContainer getTasks ();

	public void exec (Action<? super GdbSpec> action) throws IOException
	{
		var spec = getObjects().newInstance(GdbSpec.class);
		action.execute(spec);
		Gdb.exec(spec);
	}
	
	public TaskProvider<GdbExec> register (String name)
	{
		return getTasks().register(name, GdbExec.class);
	}
	
	public TaskProvider<GdbExec> register (String name, Action<? super GdbExec> action)
	{
		return getTasks().register(name, GdbExec.class, action);
	}
	
	public GdbMiLogListener logListener (File file) throws FileNotFoundException, IOException
	{
		Files.createDirectories(file.toPath().getParent());
		return new GdbMiLogListener(new OutputStreamWriter(new FileOutputStream(file)));
	}
	
	public GdbMiTestListener testListener (String symbol)
	{
		return new GdbMiTestListener(symbol);
	}
	
	public GdbMiTestListener testListener (String symbol, Action<? super GdbMiTestListener> action)
	{
		var r = new GdbMiTestListener(symbol);
		action.execute(r);
		return r;
	}
}
