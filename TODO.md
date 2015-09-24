* Incorporate Error Function into saved and loaded nodetree.
* decide if error function can be set/overridden by the argparser.
* Test that the scores are working correctly when the error functions change for a population member
* Test that is is being correclty set by the settings load from JSON

Other
=====
 * look into auto keyword for better typing across architectures
 * Option to purge non-unique nodetrees for better diversity
 * show score minus size cost in output
 * Use of exceptions for config errors
 * TestConfigException
 * Check if the nodetree weight can be added to cut score earlier to drop unsuitable trees earlier?
 * Use smaller fitness cases for profiling?
