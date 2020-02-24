package aasgard.gradle.gdb;

import org.gradle.api.Action;
import org.gradle.api.DefaultTask;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.MapProperty;
import org.gradle.api.provider.Property;


public abstract class GdbSpec extends DefaultTask
{
	// life
	
	public GdbSpec ()
	{
		super();
		getEnvironment().empty();
		getExecutable().convention("gdb");
	}
	
	// properties
		
	public abstract MapProperty<String, String> getEnvironment ();
	
	public abstract Property<String> getExecutable ();
	
	public abstract Property<Action<? super GdbMiProcess>> getScript ();
	
	public abstract RegularFileProperty getTarget ();

	// utilities
	
	public void configure (Action<? super GdbSpec> action)
	{
		action.execute(this);
	}
}
