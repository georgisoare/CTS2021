package ro.ase.acs.main;

import ro.ase.acs.readers.Reader;
import ro.ase.acs.writers.ConsoleWriter;

public class Main {
	
	public static void main(String[] args) {
		IoC ioc = new IoC();
		ioc.register(Readable.class, Reader.class);
		
		Orchestrator orchestrator = new Orchestrator(new Reader(), new ConsoleWriter());
		orchestrator.execute();
	}

}
