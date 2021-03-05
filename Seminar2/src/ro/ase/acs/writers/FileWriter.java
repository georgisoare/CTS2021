package ro.ase.acs.writers;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

import ro.ase.acs.contracts.Writeable;

public class FileWriter implements Writeable{
	

	@Override
	public void print(String message) {
		OutputStreamWriter oswriter = null;
		try {
			FileOutputStream fileOutputStream = new FileOutputStream("output.txt");
			oswriter = new OutputStreamWriter(fileOutputStream);
			try {
				oswriter.write(message);
			} catch (IOException e) {
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {	
			e.printStackTrace();
		}
		finally {
			if(oswriter != null) {
				try {
					oswriter.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			
		}
	}
}
