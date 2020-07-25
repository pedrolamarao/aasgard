package aasgard.gradle.gdb;

import org.gradle.api.Action;
import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.ListProperty;
import org.gradle.api.provider.MapProperty;
import org.gradle.api.provider.Property;

import aasgard.gdb.GdbMiListener;


public abstract class GdbSpec
{
	// life
	
	public GdbSpec ()
	{
		super();
		getEnvironment().empty();
		getTool().convention("gdb");
	}
	
	// properties
		
	public abstract MapProperty<String, String> getEnvironment ();

	public abstract ListProperty<GdbMiListener> getListeners ();
	
	public abstract Property<Action<? super GdbMiProcess>> getScript ();
	
	public abstract RegularFileProperty getTarget ();
	
	public abstract Property<String> getTool ();

	// utilities
	
	public void configure (Action<? super GdbSpec> action)
	{
		action.execute(this);
	}
}
