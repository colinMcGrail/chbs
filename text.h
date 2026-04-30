static const char * ENT_ERR = "Cannot access secure entropy source";
static const char * NO_ARG_ERR = "Option -%c requires a valid operand.\n";
static const char * HUH_OPT_ERR = "Unrecognized option: '-%c'\n";
static const char * BAD_INT_ERR = "Invalid WORDCOUNT value.\n";
static const char * NOT_INT_ERR = "Could not parse WORDCOUNT.\n";
static const char * BAD_SEP_ERR = "Could not parse SEPARATOR. Must be a printable char.\n";
static const char * CL_BOTH_ERR = "-c and -l are contradictory.\n";
static const char * USAGE = "\
Usage: chbs [-l|-c] [-s SEPARATOR] [-n WORDCOUNT]\n";
static const char * HELP = "\n\
  -l        lowercases all letters of each word\n\
  -c        capitalizes all letters of each word\n\
  -s        uses SEPARATOR as custom separator\n\
  -n        generates WORDCOUNT words\n";
static const char * HELPMSG = "\n\
Try 'chbs -h' for more information.\n";
