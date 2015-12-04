package org.weme.candy.helper;

import android.app.ProgressDialog;
import android.content.Context;
import android.widget.ProgressBar;

/**
 * ProgressDialog helper
 * @author wind
 */
public class c_progress_circle{
	private Context context;
	private ProgressDialog progressDialog;
	
	public c_progress_circle(Context context){
		this.context = context;
	}
	
	public void show(boolean isCancelable){
		if(progressDialog == null){
			progressDialog = ProgressDialog.show(context, "", "", false, true);
			progressDialog.setContentView(new ProgressBar(context));
			progressDialog.setCanceledOnTouchOutside(false);
		}else if(!progressDialog.isShowing())
			progressDialog.show();
		progressDialog.setCancelable(isCancelable);
	}
	
	public void dismiss(){
		if(progressDialog != null && progressDialog.isShowing())
			progressDialog.dismiss();
	}
}