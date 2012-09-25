# -*- coding: iso-8859-1 -*-

# 09.17/12 "very_ugly_epic_requests_methods_generator.py". For further information, contact me < neozaru @ mailoo . org >
#
# *IMPORTANT NOTE* : Reading this script can cause irreparable damage on your eyes and your brains.
# Knows effects : <enter new effect here>
#
# This script was created in order to facilitate the creation/edition of Twitter requests methods 
# It generates both methods declaration (for TwitterSession.h) and implementation (TwitterSession.cpp)

# The syntax of input file is specific :
# :: <method_name> :: <var_type> <var_name> [<default_var_value>] {,...} :: <HTTP_method (POST|GET|BOTH)> :: <request_link>
# To can paste method documentation UNDER the method (it will appears ABOVE the method, in output)

# IN THIS SCRIPT :
#
#
# Output for method declaration : ("$" prefixes indicates constants values)
# <Lines readed under method description (documentation) >
# $___request_object <method_name>( <var_type> <var_name> [ = <default_value ] [,...] );
#
#


# Output for method body : ("$" prefixes indicates constants values)
# <Lines readed under method description (documentation) >
# $___request_object <method_name>( <var_type> <var_name> [,...] ) {
#	$___request_object req = $___make_request_function( ? );
#   req->$___add_function( $___map_macro( <var_name> [,...] ) );
#	return req;
# }


# Output for constants generated with request_links
# namespace <NAMESPACE> {
#	const std::string <NAMESPACE> = <namespace>/
#
#   const std::string <CONST_NAME1> = <NAMESPACE>+<const_name1>
#   const std::string <CONST_NAME2> = <NAMESPACE>+<const_name2>	 
#	[...]
#};
#


import sys, codecs, shutil

# Groups all constants used by functions.
class Tw_ConstantS:
	"""appears
	appears"""
	def __init__(self):
		self.constants = []
		self.namespaces = []


		self.___main_namespace = "TwitterConsts"

	def addNamespace(self,namespace):
		if namespace not in self.namespaces:
			self.namespaces.append(namespace)

	def addConst(self,link):
		if link not in self.constants:
			tab = link.split("/")
			
			l_namespace = tab[0].upper()
			self.addNamespace( l_namespace )

			sublink = tab[1]
			if len(tab) > 2:
				sublink += "/"+tab[2]
				if len(tab) > 3:
					sublink += "/"+tab[3]

			const_obj = Tw_Constant( l_namespace, sublink )

			self.constants.append(const_obj)
			return const_obj

	def delConst(self,const):
		if const in self.constants:
			self.constants.delete(const)

	def getMainNamespace(self):
		return self.___main_namespace


	def gen_space(self):
		rstr = "\n"+self.___main_namespace+" {\n"
		for n in self.namespaces:
			current_namespace = n
			rstr += "\n\tnamespace "+current_namespace+" {\n\n"
			rstr += "\t\tconst std::string "+n+" = \""+n.lower()+"/"+"\";\n\n"
			for c in self.constants:
				if c.getNamespace() == current_namespace:
					rstr += "\t\t"+c.gen_line()+"\n"

			rstr += "\t};\n"

		rstr += "\n};\n"
		return rstr

# Constants are used for Twitter API links
class Tw_Constant:
	""" Twitter Constants used for links
		- Complete link
		- Namespace of the constant
	"""
	def __init__(self,namespace,const_name):
		self.sublink = const_name
		self.const_name = const_name.split("/")[0]
		self.namespace = namespace

	def getNamespace(self):
		return self.namespace.upper()

	def getConstName(self):
		return self.const_name.upper()

	def gen_line(self):
		rstr = ""
		rstr += "const std::string "+self.getConstName()+" = "+self.getNamespace()+"+\""+self.sublink+"\""+";"
		return rstr

class Tw_Method:
	""" Twitter Request Method
	- Name of the method (whithout suffix)
	- List of Tw_Parameter(s)
	- HTTP method(s) ("GET","POST", or "BOTH")
	- Documentation lines """	
	def __init__(self,cm,name,method,request_link):
		
		#  CONSTANTS
		self.___request_object = "TwitterRequest*"
		self.___make_request_function = "__make_a_request"
		self.___class_name = "TwitterSession"
		self.___put_in_URL = "PUT_IN_URL"
		self.___map_macro = "REC_ARGS_<nb>"
		self.___add_function = "set_"+method+"_data"
		self.___suffix = "_request"
		self.___ext = "JSON"
		#

		self.name = name
		self.parameters = [] 
		self.http_method = method
		self.request_link = request_link
		self.request_const = cm.addConst(request_link)
		self.documentation = ""
		self.cm = cm

		# Set if a param must be directly into the request ( ex : .../tweets/:id )
		# If this param is set, it will not appear in GET/POST data
		self.param_in_request = None



	def addDoc(self,doc):
		self.documentation += doc

	def addParameter(self,parameter):
		pattern = ":"+parameter.name
		if pattern in self.request_link:
			#print("Adding pattern : " + pattern)
			self.param_in_request = parameter

		self.parameters.append(parameter)

	def gen_declaration(self,inc_doc):

		rstr = ""

		if inc_doc == 1:
			rstr += self.documentation

		rstr += self.___request_object+" "+self.name+self.___suffix+"( "
		for p in self.parameters:
			if p != self.parameters[0]:
				# Omnomnomnom
				rstr += "\t\t\t\t\t\t\t\t\t\t"
			rstr += p.to_str_h()
			if p != self.parameters[-1]:
				rstr += ", \n"
		rstr += " );\n"

		return rstr

	def gen_function(self,inc_doc):

		rstr = ""

		if inc_doc == 1:
			rstr += self.documentation

		rstr += self.___request_object+" "+self.___class_name+"::"+self.name+self.___suffix+"( "
		for p in self.parameters:
			rstr += p.to_str()
			if p != self.parameters[-1]:
				rstr += ", "

		rstr += " ) {\n"	
		rstr += self.gen_body()
		rstr += "\n}\n"

		return rstr

	def gen_body(self):
		rstr = ""

		link_constant = self.cm.getMainNamespace()+"::"+self.request_const.getNamespace()+"::"+self.request_const.getConstName()
		
		# Copy a temporary list from the parameters list
		my_parameters = self.parameters[:]

		rstr += "\t"+self.___request_object+" req = "+self.___make_request_function+"( "
		if self.param_in_request != None:
			rstr += "\n\t\t"+self.___put_in_URL+"( "+link_constant+", "+self.param_in_request.name+" )\n\t"
			my_parameters.remove(self.param_in_request)
		else:
			rstr += link_constant
		rstr += " );\n"

		if len(my_parameters) > 0:
			rstr += "\t"+"req->"+self.___add_function+"( "
			rstr += self.___map_macro.replace("<nb>",str(len(my_parameters)))+"( "
			for p in my_parameters:
				rstr += p.name
				if p != my_parameters[-1]:
					rstr += ", "

			rstr += " )"+" );"

		rstr += "\n\treturn req;";

		return rstr


	def debug(self,pdoc):
		print("Method (" + self.http_method + ") : "+self.name)
		for p in self.parameters:
			p.debug()
		if pdoc == 1:
			print("DOC : "+self.documentation)

class Tw_Parameter:
	""" Twitter Parameter
	- Type of variable ("float","int","string","bool")
	- Name of the variable
	- Default value (empty, or a value or "DEF") 
		"DEF" is used when variable has not default value, but is optional """
	
	def __init__(self,p_type,name):
		
		#  CONSTANTS
		___string_type = "std::string"
		#

		if p_type == "string":
			self.p_type = ___string_type
		else:
			self.p_type = p_type

		self.name = name
		self.default_value = ""

	def setDefaultValue(self,dv):
		self.default_value = dv

	def to_str(self):
		rstr = self.p_type+" "+self.name
		return rstr

	def to_str_h(self):
		rstr = self.to_str()
		if self.default_value != "":
			if self.default_value == "DEF":
				if "string" in self.p_type:
					rstr += " = S_UN"
				else:
					rstr += " = N_UN"

			else:
				rstr += " = "+self.default_value

		return rstr

	def debug(self):
		print("Parameter : "+self.name+" | " + self.p_type + " | = " + self.default_value )

def clean_list(p_list):
	cleaned_list = []
	for l in p_list:
		if l != '':
			cleaned_list.append(l.strip())

	return cleaned_list

def parse_parameter(p_str):
	tab = clean_list( p_str.split(" ") )
	default_value = ""

	parameter = Tw_Parameter(tab[0].strip(),tab[1].strip())
	if len(tab) > 2:
		parameter.setDefaultValue(tab[2])

	return parameter

def parse_method(cm,p_str):
	tab = p_str.split("::")
	if len(tab) == 5:
		method = Tw_Method(cm,tab[1].strip(),tab[3].strip(),tab[4].strip())

		tab_vars = tab[2].split(",")
		for p in tab_vars:
			param = parse_parameter(p)
			method.addParameter( param )

		return method

def parse_file(cm,file_in):
	methods = []
	current_method = None
	for line in file_in:
		if line[:2] == "::":
			if current_method is not None:
				methods.append(current_method)
			current_method = parse_method(cm,line)

		elif current_method is not None:
			current_method.addDoc(line)
			
	if current_method not in methods:
		methods.append(current_method)

	return methods

# Will remove all previously generated methods declaration or definition, using patterns comment in file.
def remove_from_file(file_name,pattern):
	cutting = 0
	file_out = open(file_name,"r+")
	with open(file_name) as infile, open(file_name+".cut","w") as outfile:
	    for i,line in enumerate(infile):
	    	if "BEGIN_"+pattern in line:
	    		cutting = 1
	    		outfile.write("/* HERE_"+pattern+" */\n")
	    	if not cutting:
	    		outfile.write(line)
	    	if "END_"+pattern in line:
	    		cutting = 0


	shutil.move(file_name+".cut",file_name)


# Will write methods body (or declaration) in source file (or header file)
# Argments : (Methods list, Output file name, Pattern to recognize where to write, body(1) or decl(0) )
def write_in_file(method_list,file_name,pattern,body_or_decl):
	file_out = open(file_name,"r+")
	with open(file_name) as infile, open(file_name+".out","w") as outfile:
	    for i,line in enumerate(infile):
	        if "HERE_"+pattern in line:
	        	outfile.write("/* BEGIN_"+pattern+" */\n")
	        	for m in method_list:
	        		if body_or_decl == 1:
	        			outfile.write( m.gen_function(0) )
	        		else:
	        			outfile.write( m.gen_declaration(1) )
	        		outfile.write("\n")
	        	outfile.write("/* END_"+pattern+" */\n")
	        else:
	        	outfile.write(line)
	shutil.move(file_name+".out",file_name)


if len(sys.argv) != 3 :
	print "Usage : "+sys.argv[0]+" <file_to_parse> <output_file_whithout_ext>"
	print "--> <output_file> will be auto-completed by \".h/.cpp\" (input) and \".out\" (output)"
	sys.exit(1)

def is_file_exists(filename):
	try:
   		with open(filename) as f: pass
	except IOError as e:
   		return 0

   	return 1

file_name_in = sys.argv[1]
file_name_out = sys.argv[2]

in_exists = 1
out_h_exists = 1


if not is_file_exists(file_name_in):
	print(file_name_in + " : file not found") 
	sys.exit(1)

if is_file_exists(file_name_out+".cpp"):
	print("Ouput file '" + file_name_out + ".cpp" + "' already exists. Saving old file to '" + file_name_out + ".cpp.old'")
	shutil.copy(file_name_out + ".cpp", file_name_out+".cpp.old")

if is_file_exists(file_name_out+".h"):
	print("Ouput file '" + file_name_out + ".h" + "' already exists. Saving old file to '" + file_name_out + ".h.old'")
	shutil.copy(file_name_out + ".h", file_name_out+".h.old")


file_in = open(file_name_in,"r")
cm = Tw_ConstantS()
methods = parse_file(cm,file_in)

#debug
#for m in methods:
#	print(m.gen_declaration(1))
#	print(m.gen_function(0))

pattern = "PYGEN" 
# That means : 
# HERE_PYGEN will be the location of generated code (put comment /* HERE_PYGEN */ in your code) 
# BEGIN_PYGEN will be printed as comment before generated code 
# END_PYGEN will be printed as comment after generated code 

remove_from_file(file_name_out+".cpp",pattern)
remove_from_file(file_name_out+".h",pattern)


write_in_file(methods,file_name_out+".cpp",pattern,1)
write_in_file(methods,file_name_out+".h",pattern,0)

#constants_file = open("TwitterConstants.h.out")
# twc.addConst("statuses/mention_timeline")
# twc.addConst("twits/truc_chouette")
#print( cm.gen_space() )
