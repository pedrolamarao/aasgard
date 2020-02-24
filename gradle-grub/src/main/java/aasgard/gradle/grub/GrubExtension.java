package aasgard.gradle.grub;

import javax.inject.Inject;

import org.gradle.api.Action;
import org.gradle.api.tasks.TaskContainer;
import org.gradle.api.tasks.TaskProvider;

public abstract class GrubExtension 
{
	@Inject
	public abstract TaskContainer getTasks();
	
	public TaskProvider<GrubRescueCompile> registerRescue (String name)
	{
		return getTasks().register(name, GrubRescueCompile.class);
	}
	
	public TaskProvider<GrubRescueCompile> registerRescue (String name, Action<? super GrubRescueCompile> action)
	{
		return getTasks().register(name, GrubRescueCompile.class, action);
	}
	
	public TaskProvider<GrubStandaloneCompile> registerStandalone (String name)
	{
		return getTasks().register(name, GrubStandaloneCompile.class);
	}
	
	public TaskProvider<GrubStandaloneCompile> registerStandalone (String name, Action<? super GrubStandaloneCompile> action)
	{
		return getTasks().register(name, GrubStandaloneCompile.class, action);
	}
}
