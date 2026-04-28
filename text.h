const char * ENT_ERR = "Cannot access secure entropy source";
const char * NO_ARG_ERR = "Option -%c requires a valid operand.\n";
const char * HUH_OPT_ERR = "Unrecognized option: '-%c'\n";
const char * BAD_INT_ERR = "Invalid WORDCOUNT value.\n";
const char * NOT_INT_ERR = "Could not parse WORDCOUNT.\n";
const char * BAD_SEP_ERR = "Could not parse SEPARATOR. (valid separators: ASCII 32-126)\n";
const char * USAGE = "\
Usage: chbs [-c|-C] [-n] [-w WORDCOUNT]\n\
   or: chbs [-c|-C] -s SEPARATOR [-w WORDCOUNT]\n";
const char * HELP = "\n\
  -c        capitalizes first letter of each word\n\
  -C        capitalizes all letters of each word\n\
  -n        does not print a separator between each character\n\
  -s        uses SEPARATOR as custom separator (valid separators: ASCII 32-126)\n\
  -w        prints WORDCOUNT words\n";
const char * HELPMSG = "\n\
Try 'chbs -h' for more information.\n";
