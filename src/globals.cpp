/** Global class contains all of the variables and constants that
 * might be useful anywhere in the program.
 *
 * It is not meant to facilitate object binding, data logging,
 * or error trapping.
 *
 * There is a mutex protecting all mutable data elements of
 * the class.  It is kept coarse-grained on purpose, to prevent
 * use cases where the global data structure gets abused.
 * If you are hitting globals so often that you want domain-
 * specific mutexes, you might want 
 *
 */

namespace DuckSim {

  Globals() {
    return;
  } //end: Globals (constructor)
  
  ~Globals() {
    return;
  } //end: ~Globals (destructor)
  
  /** Acquire a mutex on the global object.
   * Anticipating future use cases involving massively parallel
   * execution, all mutable data elements in the global object
   * are protected by a mutex.  Access to them should not
   * take place inside of an algorithm's innermost loop.
   *
   */
  void Globals::getLock(int domain) {
    //TODO: Implement mutex lock framework.
    return;
  } //end: getLock
  
  void Globals::releaseLock() {
    //TODO: ...
    return;
  } //end: releaseLock
  
} //end: DuckSim (namespace)

