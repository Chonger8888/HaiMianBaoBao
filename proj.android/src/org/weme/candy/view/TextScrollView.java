package org.weme.candy.view;

import android.content.Context;
import android.graphics.Color;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
/**
 * Vertical Scroll TextView
 * @author wind
 */
public class TextScrollView extends LinearLayout {
	private LinearLayout linearLayout;
	private ScrollView scrollView;
	private TextView title, content, end;
	
	public TextScrollView(Context context, AttributeSet attrs) {
		super(context, attrs);
		linearLayout = new LinearLayout(context);
		linearLayout.setOrientation(LinearLayout.VERTICAL);
		DisplayMetrics displayMetrics = new DisplayMetrics();
		((WindowManager) context.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay().getMetrics(displayMetrics);
		title = new TextView(context);
		title.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 23);
		title.setTextColor(Color.WHITE);
		title.setShadowLayer(1, 1, 3, Color.BLACK);
		title.setGravity(Gravity.CENTER_HORIZONTAL|Gravity.BOTTOM);
		linearLayout.addView(title, new LayoutParams(LayoutParams.MATCH_PARENT, displayMetrics.heightPixels));
		content = new TextView(context);
		content.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 18);
		content.setTextColor(Color.WHITE);
		content.setGravity(Gravity.CENTER);
		content.setShadowLayer(1, 1, 3, Color.BLACK);
		content.setPadding(0, 0, 0, 80);
		LayoutParams layoutParams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		linearLayout.addView(content, layoutParams);
		end = new TextView(context);
		end.setTextSize(TypedValue.COMPLEX_UNIT_DIP, 30);
		end.setTextColor(Color.WHITE);
		end.setShadowLayer(1, 1, 3, Color.BLACK);
		end.setGravity(Gravity.CENTER_HORIZONTAL|Gravity.TOP);
		linearLayout.addView(end, new LayoutParams(LayoutParams.MATCH_PARENT, displayMetrics.heightPixels/2));
		scrollView = new ScrollView(context);
		scrollView.setBackgroundColor(Color.parseColor("#88000000"));
		scrollView.setVerticalScrollBarEnabled(false);
		scrollView.addView(linearLayout, layoutParams);
		scrollView.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				return true;
			}
		});
		addView(scrollView, layoutParams);
	}
	
	/**
	 * Set scroll text
	 * @param title
	 * @param content
	 * @param end
	 */
	public void setText(String title, String content, String end){
		if(!TextUtils.isEmpty(title))
			this.title.setText(title);
		if(!TextUtils.isEmpty(content))
			this.content.setText(content);
		if(!TextUtils.isEmpty(end))
			this.end.setText(end);
	}
	
	/**
	 * Scroll the text
	 * @param y
	 * @param millisecond
	 * @param onScrollListener
	 */
	public void scrollText(int y, final int millisecond, final OnScrollListener onScrollListener){
		scrollView.scrollTo(0, 0);
		if(onScrollListener != null)
			onScrollListener.onTop();
		final int distance = (int) (getResources().getDisplayMetrics().density*y+0.5F);
		scrollView.post(new Runnable() {
			@Override
			public void run() {
				synchronized (onScrollListener) {
					scrollView.smoothScrollBy(0, distance);
					if(scrollView.getScrollY() != linearLayout.getMeasuredHeight() - scrollView.getHeight()){
						scrollView.postDelayed(this, millisecond);
					}else if(onScrollListener != null)
						onScrollListener.onBottom();
				}
			}
		});
	}
	
	/**
	 * TextScrollView scroll listener
	 * @author wind
	 */
	public interface OnScrollListener{
		void onTop();
		void onBottom();
	}

}
