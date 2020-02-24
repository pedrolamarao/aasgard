package aasgard.gradle.qemu;

import java.io.IOException;

import javax.inject.Inject;

import org.gradle.api.Action;
import org.gradle.api.model.ObjectFactory;
import org.gradle.api.tasks.TaskContainer;
import org.gradle.api.tasks.TaskProvider;

public abstract class QemuExtension 
{
	@Inject
	public abstract ObjectFactory getObjects ();

	@Inject
	public abstract TaskContainer getTasks ();

	public TaskProvider<QemuSystemExec> registerSystem (String name)
	{
		return getTasks().register(name, QemuSystemExec.class);
	}

	public TaskProvider<QemuSystemExec> registerSystem (String name, Action<? super QemuSystemExec> action)
	{
		return getTasks().register(name, QemuSystemExec.class, action);
	}
	
	public Process system (Action<? super QemuSystemSpec> configure) throws IOException
	{
		var spec = getObjects().newInstance(QemuSystemSpec.class);
		configure.execute(spec);	
		return Qemu.system(spec);
	}
}
