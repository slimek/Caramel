package com.slimek.caramel.samples.jnihelpers;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;


public class JniHelpersActivity extends Activity
{
	static
	{
		System.loadLibrary( "JniHelpers" );
	}
	
	public native void Run();
	
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState );
		
		LinearLayout layout = new LinearLayout( this );
		layout.setOrientation( LinearLayout.VERTICAL );
		
		/// Run Button ///
		
		Button runButton = new Button( this );
		runButton.setText( "Run" );
		runButton.setOnClickListener( new Button.OnClickListener()
		{
			@Override
			public void onClick( View v )
			{
				Run();
			}
		});

		layout.addView( runButton );
		
		
		/// Grid Area - 3 Text ///
		
		RelativeLayout gridArea = new RelativeLayout( this );
		
		layout.addView( gridArea );
		
		this.setContentView( layout );
	}
	
	
	//
	// Called by Native
	//
	
	static public void Salute( final String msg ) 
	{
		Log.i( "JniHelpers", "Salute: " + msg );
	}
}