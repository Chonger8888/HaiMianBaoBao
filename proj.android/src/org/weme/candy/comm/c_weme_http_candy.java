package org.weme.candy.comm;



public class c_weme_http_candy {

	/* dispatch
	 * 
	 */
	final static private java.lang.String 	   define_url_dispatch										  ="dispatch.php";

	/* web svr interface
	 * 
	 */
	//Game
	public static final java.lang.Integer	  define_url_generate_server_order							  =0;
	public static final java.lang.Integer	  define_url_comfirm_server_order							  =1;
	public static final java.lang.Integer	  define_url_guest_register									  =7;
	public static final java.lang.Integer	  define_url_guest_flagUser									  =13;
	public static final java.lang.Integer	  define_url_check_update									  =200;
	public static final java.lang.Integer	  define_url_verify_luas									  =400;
	public static final java.lang.Integer	  define_url_guest_tracker									  =500;
	public static final java.lang.Integer	  define_url_generate_unipay_order							  =1100;
	public static final java.lang.Integer	  define_url_generate_alipay_order							  =1400;
	public static final java.lang.Integer	  define_url_comfirm_unipay_order							  =1101;
	public static final java.lang.Integer	  define_url_comfirm_alipay_order							  =1401;
	public static final java.lang.Integer	  define_url_push_lift							              =310;
	public static final java.lang.Integer	  define_url_push_message							          =14;
	public static final java.lang.Integer	  define_url_lift_number							          =307;
	public static final java.lang.Integer	  define_url_user_headimg							          =10;
	public static final java.lang.Integer	  define_url_user_info							              =11;
	public static final java.lang.Integer	  define_url_svr							                  =202;
	public static final java.lang.Integer	  define_url_KKpay_order							          =2000;
	public static final java.lang.Integer	  define_url_KKpay_comfirm_order							  =2001;
	
	
	
	static public 	java.lang.String get_wh_url(int n_url_id,java.util.HashMap<String, java.lang.Object>m){java.lang.StringBuilder sb = new java.lang.StringBuilder();for(java.util.Map.Entry<String, Object> e :m.entrySet()){sb.append(e.getKey()+"="+e.getValue().toString()+"&");}return c_weme_http_candy.get_wh_url(n_url_id)+"&"+sb.toString();}
	static private 	java.lang.String get_wh_game_dispath(int n_classs,int n_cmd){return org.weme.candy.comm.c_app_define.define_url_http_game_dns_ex+c_weme_http_candy.define_url_dispatch+"?v_class="+java.lang.String.valueOf(n_classs)+"&v_cmd="+java.lang.String.valueOf(n_cmd);}
	static public 	java.lang.String get_wh_url(int n_url_id){
		   
		java.lang.String str_url = "";
		if(n_url_id == c_weme_http_candy.define_url_generate_server_order){
			str_url = c_weme_http_candy.get_wh_game_dispath(1, c_weme_http_candy.define_url_generate_server_order);
		}else if(n_url_id == c_weme_http_candy.define_url_comfirm_server_order){
			str_url = c_weme_http_candy.get_wh_game_dispath(1, c_weme_http_candy.define_url_comfirm_server_order);
//			str_url = c_weme_http_candy.get_wh_game_dispath(2000, c_weme_http_candy.define_url_comfirm_server_order);
		}else if(n_url_id == c_weme_http_candy.define_url_guest_register){
			str_url = c_weme_http_candy.get_wh_game_dispath(0, c_weme_http_candy.define_url_guest_register);
		}else if(n_url_id == c_weme_http_candy.define_url_check_update){
			str_url = c_weme_http_candy.get_wh_game_dispath(4, c_weme_http_candy.define_url_check_update);
		}else if(n_url_id == c_weme_http_candy.define_url_verify_luas){
			str_url = c_weme_http_candy.get_wh_game_dispath(800, c_weme_http_candy.define_url_verify_luas);
		}else if(n_url_id == c_weme_http_candy.define_url_guest_tracker){
			str_url = c_weme_http_candy.get_wh_game_dispath(500, c_weme_http_candy.define_url_guest_tracker);
		}else if(n_url_id == c_weme_http_candy.define_url_generate_unipay_order){
			str_url = c_weme_http_candy.get_wh_game_dispath(1100, c_weme_http_candy.define_url_generate_unipay_order);
		}else if(n_url_id == define_url_comfirm_unipay_order){
			str_url = c_weme_http_candy.get_wh_game_dispath(1100, c_weme_http_candy.define_url_comfirm_unipay_order);
		}else if(n_url_id == define_url_guest_flagUser){
			str_url = c_weme_http_candy.get_wh_game_dispath(0, c_weme_http_candy.define_url_guest_flagUser);
		}else if(n_url_id == define_url_push_lift){
			str_url = c_weme_http_candy.get_wh_game_dispath(300, c_weme_http_candy.define_url_push_lift);
		}else if (n_url_id == define_url_lift_number){
			str_url = c_weme_http_candy.get_wh_game_dispath(300, c_weme_http_candy.define_url_lift_number);
		}else if (n_url_id == define_url_push_message){
			str_url = c_weme_http_candy.get_wh_game_dispath(0, c_weme_http_candy.define_url_push_message);
		}else if (n_url_id == define_url_generate_alipay_order) {
			str_url = c_weme_http_candy.get_wh_game_dispath(1400, c_weme_http_candy.define_url_generate_alipay_order);
		}else if (n_url_id == define_url_comfirm_alipay_order) {
			str_url = c_weme_http_candy.get_wh_game_dispath(1400, c_weme_http_candy.define_url_comfirm_alipay_order);
		}else if(n_url_id == define_url_user_headimg){
			str_url = c_weme_http_candy.get_wh_game_dispath(0, c_weme_http_candy.define_url_user_headimg);
		}else if (n_url_id == define_url_user_info) {
			str_url=c_weme_http_candy.get_wh_game_dispath(0,0);
		}else if(n_url_id == define_url_svr){
			str_url = "http://weme.wemepi.com/2.0.4/dispatch.php?v_class=200&v_cmd=202";
		}else if(n_url_id == define_url_KKpay_order) {
			str_url = c_weme_http_candy.get_wh_game_dispath(2000, 0);
		}else if (n_url_id == define_url_KKpay_comfirm_order) {
			str_url = c_weme_http_candy.get_wh_game_dispath(2000, 1);
		}
		return str_url;
	}
}
