package aasgard.gradle.grub;

import org.gradle.api.Action;
import org.gradle.api.file.DirectoryProperty;
import org.gradle.api.file.RegularFileProperty;
import org.gradle.api.provider.ListProperty;
import org.gradle.api.provider.Property;

public abstract class GrubSpec
{
	public abstract Property<String> getFormat ();

	public abstract ListProperty<String> getFonts ();

	public abstract ListProperty<String> getInstall ();

	public abstract ListProperty<String> getLoad ();
	
	public abstract ListProperty<String> getLocales ();
	
	public abstract RegularFileProperty getSource ();
	
	public abstract DirectoryProperty getTemporary ();
	
	public abstract ListProperty<String> getThemes ();
	
	public abstract RegularFileProperty getTarget ();
	
	public abstract Property<String> getTool ();
	
	public void configure (Action<? super GrubSpec> action)
	{
		action.execute(this);
	}
}
