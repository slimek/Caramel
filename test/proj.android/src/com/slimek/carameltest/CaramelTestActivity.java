package com.slimek.carameltest;

import android.app.Activity;
import android.os.Bundle;


public class CaramelTestActivity extends Activity
{
	static
	{
		System.loadLibrary( "CaramelTest" );
	}
	
	public native void Run();
	
	@Override
	public void onCreate( Bundle savedInstanceState )
	{
		super.onCreate( savedInstanceState );
		
		Run();
	}
}