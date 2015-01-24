/**
 * <p>Title: gpNoCsim - General Purpose Netowork-on-Chip Simulation
 * 	  					Framework</p>
 *  * <p>Developed: Department of Computer Science and Engineering</p>
 * @version 1.0
 */

/**
 * gpNoCsim is the starting class of the simulator.
 * <p>
 * Contains the main method and initiates the {@link Controller} instance.
 * 
 * @version 1.0
 * 
 */
public class gpNoCsim {

	/**
	 * starting point of the simulator
	 * 
	 * @param args
	 *            command line arguements
	 * @see Controller
	 */
	public static void main(String[] args) {
		Controller controller = new Controller();
		controller.main_loop();
	}
}
