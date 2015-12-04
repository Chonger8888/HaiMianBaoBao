package org.weme.candy.data.bean;
/**
 * 用户BEAN
 * @author wind
 * @since 2013-11-22
 */
public class c_user_bean {
	private String idx;									//ID
	private String account;								//帐号
	private String password;							//密码
	private String gender;								//性别
	private String avatarUrl;							//头像地址
	private String nickname;							//昵称
	/**
	 * @return the idx
	 */
	public String getIdx() {
		return idx == null ? "":idx;
	}
	/**
	 * @param idx the idx to set
	 */
	public void setIdx(String idx) {
		this.idx = idx;
	}
	/**
	 * @return the account
	 */
	public String getAccount() {
		return account == null ? "":account;
	}
	/**
	 * @param account the account to set
	 */
	public void setAccount(String account) {
		this.account = account;
	}
	/**
	 * @return the password
	 */
	public String getPassword() {
		return password == null ? "":password;
	}
	/**
	 * @param password the password to set
	 */
	public void setPassword(String password) {
		this.password = password;
	}
	/**
	 * @return the gender
	 */
	public String getGender() {
		return gender == null ? "":gender;
	}
	/**
	 * @param gender the gender to set
	 */
	public void setGender(String gender) {
		this.gender = gender;
	}
	/**
	 * @return the avatarUrl
	 */
	public String getAvatarUrl() {
		return avatarUrl == null ? "":avatarUrl;
	}
	/**
	 * @param avatarUrl the avatarUrl to set
	 */
	public void setAvatarUrl(String avatarUrl) {
		this.avatarUrl = avatarUrl;
	}
	/**
	 * @return the nickname
	 */
	public String getNickname() {
		return nickname == null ? "":nickname;
	}
	/**
	 * @param nickname the nickname to set
	 */
	public void setNickname(String nickname) {
		this.nickname = nickname;
	}
	
	
}
