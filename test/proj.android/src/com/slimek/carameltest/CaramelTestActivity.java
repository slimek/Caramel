package com.slimek.carameltest;

import android.app.Activity;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;


public class CaramelTestActivity extends Activity
{
	static
	{
		System.loadLibrary( "CaramelTest" );
	}
	
	public native void Run( AssetManager mgr );
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState );

		LinearLayout layout = new LinearLayout( this );
		layout.setOrientation( LinearLayout.VERTICAL );
		
		TextView text = new TextView( this );
		text.setText( "Caramel Test" );
		
		Button startButton = new Button( this );
		startButton.setText( "Start" );
		startButton.setOnClickListener(
			new OnClickListener()
			{
				@Override
				public void onClick( View view )
				{
					Run( getResources().getAssetManager() );
				}
			}
		);
		
		layout.addView( text );
		layout.addView( startButton );
		this.setContentView( layout );
	}
}
