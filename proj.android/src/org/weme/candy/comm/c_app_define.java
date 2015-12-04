package org.weme.candy.comm;
public class c_app_define {

	/* application version
	 * 
	 */
	final static public java.lang.Integer 		define_app_version	 								= 16														;
	final static public java.lang.String		define_app_outer_version							= "3.0.2.guest.mini"											;
	final static public java.lang.Boolean		define_app_current_is_release_version				= true													;
	final static public java.lang.Boolean		define_app_log_file_tracker							= true													;
 
	
	/* android app market signature
	 * 
	 */
	final public static java.lang.String		define_android_app_market_signature					= "00000000"											;

	/* app package name 
	 * 
	 */
	final public static 	String				define_app_package_name								= "org.weme.candy"										;

	/* web svr dir
	 */
	final public static java.lang.String 		define_url_http_game_dns							= "http://guest.candy.weme-game.com/"					;
	final public static java.lang.String 		define_url_http_game_dns_ex							= define_url_http_game_dns+define_app_outer_version+"/"	;
}