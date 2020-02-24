package aasgard.gradle.gdb;

import java.io.IOException;

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
}
