package aasgard.gradle.gdb;

import org.gradle.api.Plugin;
import org.gradle.api.Project;

public class GdbPlugin implements Plugin<Project>
{
	@Override
    public void apply (Project project) 
    {
		project.getExtensions().create("gdb", GdbExtension.class);
    }
}
