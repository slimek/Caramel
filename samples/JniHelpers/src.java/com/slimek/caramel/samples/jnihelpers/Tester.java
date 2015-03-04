package com.slimek.caramel.samples.jnihelpers;

import android.util.Log;

public class Tester
{
	public int number = 123;
	public String name = "Tester";
	
	public Tester()
	{
		Log.i( "Tester", "Created" );
	}
	
	public void ChangeNumber( int newNumber )
	{
		number = newNumber;
	}
}
