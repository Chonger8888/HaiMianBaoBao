package org.weme.candy.data.database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;
/**
 * 数据库操作类
 * @author wind
 * @since 2013-11-19
 */
public class c_candy_db extends SQLiteOpenHelper{
	private static final int DB_VERSION = 1;
	private static c_candy_db insatnce = null;
	
	private c_candy_db(Context context, String name, CursorFactory factory, int version) {
		super(context, name, factory, version);
	}
	
	public static final String WEME_CANDY_DB = "weme_candy.db";
	public static synchronized c_candy_db get_candy_db(Context context){
		if(insatnce == null){
			synchronized (c_candy_db.class) {
				if(insatnce == null)
					insatnce = new c_candy_db(context, WEME_CANDY_DB, null, DB_VERSION);
			}
		}
		return insatnce;
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		create_tables(db);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		drop_tables(db);
		create_tables(db);
	}
	
	
	
	private void create_tables(SQLiteDatabase db){
		
	}
	
	private void drop_table(SQLiteDatabase db, String table){
		db.execSQL("DROP TABLE IF EXISTS ["+table+"];drop table ["+table+"]");
	}
	
	private void drop_tables(SQLiteDatabase db){
		
	}
	
}
