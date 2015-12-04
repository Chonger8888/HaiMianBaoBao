package org.weme.candy.data.bean;

import org.json.JSONObject;

import android.text.TextUtils;

public class c_version_bean {
	private String versionName;												//版本名
	private String updateInfo;												//新版本信息
	private String status;													//是否强制更新： 0 正常更新；1强制更新
	private String apkURL;													//APK下载地址
	private String appName;													//APP名字
	private String appVersionInner;											//内部版本号
	private String localSavedPath;											//服务器最新版本保存地址
	public static final String UPDATE_STATUS_NORMAL = "0";
	public static final String UPDATE_STATUS_FORCE = "1";
	
	public String getVersionName() {
		return versionName;
	}
	public void setVersionName(String versionName) {
		this.versionName = versionName;
	}
	public String getUpdateInfo() {
		return updateInfo;
	}
	public void setUpdateInfo(String updateInfo) {
		this.updateInfo = updateInfo;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public String getApkURL() {
		return apkURL;
	}
	public void setApkURL(String apkURL) {
		this.apkURL = apkURL;
	}
	public String getAppName() {
		return appName;
	}
	public void setAppName(String appName) {
		this.appName = appName;
	}
	public String getAppVersionInner() {
		return appVersionInner;
	}
	public void setAppVersionInner(String appVersionInner) {
		this.appVersionInner = appVersionInner;
	}
	public String getLocalSavedPath() {
		return localSavedPath;
	}
	public void setLocalSavedPath(String localSavedPath) {
		this.localSavedPath = localSavedPath;
	}
	
	/**
	 * 把JSON转换为c_version_bean，可能为null
	 * @param json
	 * @return c_version_bean
	 */
	public static c_version_bean parseJson2VersionBean(String json){
		c_version_bean version = null;
		if(!TextUtils.isEmpty(json) && json.contains("{\"status\":0,\"id\":200,")){
			try {
				JSONObject jsonObject = new JSONObject(json).getJSONObject("content");
				version = new c_version_bean();
				version.setVersionName(jsonObject.getString("title"));
				version.setUpdateInfo(jsonObject.getString("update_info"));
				version.setStatus(jsonObject.getString("status"));
				version.setApkURL(jsonObject.getString("down_url"));;
				version.setAppName(jsonObject.getString("app_name"));;
				version.setAppVersionInner(jsonObject.getString("version"));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return version;
	}
}