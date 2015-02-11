package com.slimek.caramel.samples.jnihelpers;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;


public class JniHelpersActivity extends Activity
{
	static
	{
		System.loadLibrary( "JniHelpers" );
	}
	
	public native void Run();
	
	
	static private JniHelpersActivity m_instance = null;
	
	private TextView m_label1 = null;
	private TextView m_label2 = null; 
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState );
		
		m_instance = this;
		
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
		
		m_label1 = new TextView( this );
		m_label1.setText( "Label 1" );
		m_label1.setId( 1 );
		gridArea.addView( m_label1 );
		
		RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
			RelativeLayout.LayoutParams.WRAP_CONTENT,
			RelativeLayout.LayoutParams.WRAP_CONTENT
		);
		
		lp.addRule( RelativeLayout.RIGHT_OF, m_label1.getId() );
		lp.leftMargin = 20;
		
		m_label2 = new TextView( this );
		m_label2.setText( "Label 2" );
		m_label2.setId( 2 );
		gridArea.addView( m_label2, lp );
		
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
	
	static public Object Instance()
	{
		Log.i( "JniHelpers", "Instance" );
		return m_instance;
	}
	
	public Object GetLabel( final int index )
	{
		switch ( index )
		{
		case 1: return m_label1;
		case 2: return m_label2;
		default: return null;
		}
	}
}