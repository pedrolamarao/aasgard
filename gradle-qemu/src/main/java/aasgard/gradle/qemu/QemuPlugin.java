package aasgard.gradle.qemu;

import org.gradle.api.Plugin;
import org.gradle.api.Project;

public class QemuPlugin implements Plugin<Project>
{
	@Override
    public void apply (Project project) 
    {
		project.getExtensions().create("qemu", QemuExtension.class);
    }
}
