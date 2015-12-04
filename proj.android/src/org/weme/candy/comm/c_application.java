package org.weme.candy.comm;

import java.io.File;

import org.weme.candy.util.CppCallJava;


import android.app.Application;
import android.content.res.Configuration;

/**
 * @author leaf
 */
public class c_application extends Application{
	
	private static c_application instance;
	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
	}

	public static c_application getinstance(){
		return instance;
	}
    

	


	public void DeleteFile(File file) {
		if (!file.exists()) {
			return;
		} else {
			if (file.isFile()) {
				file.delete();
				return;
			}
			if (file.isDirectory()) {
				File[] childFile = file.listFiles();
				if (childFile == null || childFile.length == 0) {
					file.delete();
					return;
				}
				for (File f : childFile) {
					DeleteFile(f);
				}
				file.delete();
			}
		}
	}
	
}
