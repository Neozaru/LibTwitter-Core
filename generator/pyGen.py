# -*- coding: iso-8859-1 -*-

# 09.17/12 "very_ugly_epic_requests_methods_generator.py". For further information, contact me < neozaru @ mailoo . org >
#
# *IMPORTANT NOTE* : Reading this script can cause irreparable damage on your eyes and your brain.
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
import datetime

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
		#if link not in self.constants:
		tab = None
		l_namespace = link
		sublink = link

		if "http://" in link or "https://" in link:
			sublink = link.replace("https://","").replace("http://","")
			l_namespace = "STREAMS"
			self.addNamespace(l_namespace)
		else:
			tab = link.split("/")
	
			if len(tab) > 1:
				l_namespace = tab[0].upper()
				self.addNamespace( l_namespace )
				sublink = tab[1]
				if len(tab) > 2:
					sublink += "/"+tab[2]
					if len(tab) > 3:
						sublink += "/"+tab[3]

		const_obj = Tw_Constant( l_namespace, sublink )

		# Checks if const is already indexed
		for c in self.constants:
			if c.getNamespace() == const_obj.getNamespace():
				if c.getConstName() == const_obj.getConstName():
					return const_obj

		self.constants.append(const_obj)
	
		return const_obj

	def delConst(self,const):
		if const in self.constants:
			self.constants.delete(const)

	def getMainNamespace(self):
		return self.___main_namespace

	def gen_space(self):
		rstr = ""

		for n in self.namespaces:
			current_namespace = n
			rstr += "\n\tnamespace "+current_namespace+" {\n\n"
			rstr += "\t\tconst std::string "+n+" = \""+n.lower()+"/"+"\";\n\n"
			for c in self.constants:
				if c.getNamespace() == current_namespace:
					rstr += "\t\t"+c.gen_line()+"\n"

			rstr += "\t};\n"

		return rstr

# Constants are used for Twitter API links
class Tw_Constant:
	""" Twitter Constants used for links
		- Complete link
		- Namespace of the constant
	"""
	def __init__(self,namespace,const_name):

		self.namespace = namespace
		self.sublink = const_name


		self.const_name = const_name
		const_tab = const_name.split("/")

		if len(const_tab) > 1:
			self.const_name = const_name.split("/")[0]
	

	def getNamespace(self):
		return self.namespace.upper()

	def getConstName(self):
		if "." in self.const_name:
			return self.const_name.split(".")[0].upper()
		return self.const_name.upper()

	def gen_line(self):
		api_link = "API_LINK"


		rstr = "const std::string "

		cn = self.getConstName()
		ns = self.getNamespace()

		if "STREAM" in cn:
			cn = cn.split(".")[0].upper()
			api_link = "PROTOCOL"
			ns = "\"\""

		rstr += cn+" = "+api_link+" + "+ns+" + \""+self.sublink+"\""+" + FORMAT"+" ;"

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
		self.___class_name = "RequestCreator"
		self.___put_in_URL = "PUT_VAR_IN_URL"
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

			self.param_in_request = parameter

		self.parameters.append(parameter)

	def getName(self):
		return self.name

	def getParameters(self):
		return self.parameters

	def gen_declaration(self,inc_doc):

		rstr = ""

		rstr += self.gen_doc()

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


		link_constant = self.cm.getMainNamespace()
		if self.request_const.getNamespace() != "" and self.request_const.getNamespace() != self.request_const.getConstName():
			link_constant += "::"+self.request_const.getNamespace()
		link_constant += "::"+self.request_const.getConstName()
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

	def gen_doc(self):

		twitter_link = "http://dev.twitter.com/docs/api/1.1/"+self.http_method.lower()+"/"+self.request_link
		text = "Twitter Documentation for ["+self.name+"]"

		rstr = ""
		rstr += "/**\n"
		
		rstr += "* \htmlonly \n"
		rstr += "* <a target=\"_blank\"href=\""+twitter_link+"\">"+text+"<a>"
		rstr += "\n* \endhtmlonly\n"

		rstr += "* \latexonly \n"
		rstr += "* \href{"+twitter_link+"}{"+text.replace("_","\_")+"}"
		rstr += "\n* \endlatexonly\n"

		rstr += "*/\n"

		return rstr

	def debug(self,pdoc):
		print("Method (" + self.http_method + ") : "+self.name)
		for p in self.parameters:
			p.debug()
		if pdoc == 1:
			print("DOC : "+self.documentation)

	def gen_test(self,overload):

		test_name = self.name
		if overload != 0:
			test_name += "_"+str(overload)

		rstr = ""
		rstr += "void "+test_name+"_test("

		rstr += ") {\n"

		rstr += "\ttest_request( "

		rstr += "_session->"+self.name+"_request("

		first_arg = 1
		for p in self.parameters:
			if not p.hasDefaultValue():
				if first_arg:
					first_arg = 0
				else:
					rstr += ","
				rstr += "DEF_"+p.getType().upper()

		rstr += ""

		rstr += ") "

		rstr += ");\n"

		rstr += "}\n\n"

		return rstr

class Tw_Parameter:
	""" Twitter Parameter
	- Type of variable ("float","int","string","bool")
	- Name of the variable
	- Default value (empty, or a value or "DEF") 
		"DEF" is used when variable has not default value, but is optional """
	
	def __init__(self,p_type,name):
		
		#  CONSTANTS
		#___string_type = "const std::string&"
		___string_type = "str_t"
		#

		if p_type == "string":
			self.p_type = ___string_type
		else:
			self.p_type = p_type

		self.name = name
		self.default_value = ""

	def setDefaultValue(self,dv):
		self.default_value = dv

	def hasDefaultValue(self):
		return ( self.default_value != "" )

	def getType(self):
		return self.p_type

	def to_str(self):
		rstr = self.p_type+" "+self.name
		return rstr

	def to_str_h(self):
		rstr = self.to_str()
		if self.default_value != "":
			if self.default_value == "DEF":
				str_types = ["str_t","string","twt_id_t","cur_id_t","usr_id_t","slug_t","lang_t","usr_name_t"]
				if self.p_type not in str_types:
					rstr += " = DEF_NUM"
				else:
					rstr += " = DEF_STR"

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

		#proto = tab[3].strip()
		#get_post = proto
		#stream = 0

		method = Tw_Method( cm, tab[1].strip(), tab[3].strip(), tab[4].strip() )

		tab_vars = tab[2].split(",")

		for p in tab_vars:
			if p != " ":
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

		elif line[:1] != "#" and current_method is not None:
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
	    		outfile.write("/* HERE_"+pattern+" don't remove this comment */\n")
	    	if not cutting:
	    		outfile.write(line)
	    	if "END_"+pattern in line:
	    		cutting = 0


	shutil.move(file_name+".cut",file_name)


# Will write methods body (or declaration) in source file (or header file)
# Argments : (Methods list, Output file name, Pattern to recognize where to write, body(1) or decl(0) )
def write_in_file(method_list,file_name,pattern,body_or_decl):
	t = datetime.datetime.now()
	file_out = open(file_name,"r+")
	with open(file_name) as infile, open(file_name+".out","w") as outfile:
	    for i,line in enumerate(infile):
	        if "HERE_"+pattern in line:
	        	outfile.write("/* BEGIN_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")
	        	for m in method_list:
	        		if body_or_decl == 1:
	        			outfile.write( m.gen_function(0) )
	        		else:
	        			outfile.write( m.gen_declaration(1) )
	        		outfile.write("\n")
	        	outfile.write("/* END_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")
	        else:
	        	outfile.write(line)
	shutil.move(file_name+".out",file_name)

def write_constants_file(file_name,consts):
	t = datetime.datetime.now()
	file_out = open(file_name,"r+")
	with open(file_name) as infile, open(file_name+".out","w") as outfile:
	    for i,line in enumerate(infile):
	        if "HERE_"+pattern in line:
	        	outfile.write("/* BEGIN_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")
	        	outfile.write(consts.gen_space())
	        	outfile.write("\n")
	        	outfile.write("/* END_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")
	        else:
	        	outfile.write(line)
	shutil.move(file_name+".out",file_name)


def write_test_suite(file_name,methods,pattern):
	t = datetime.datetime.now()
	file_out = open(file_name,"r+")
	with open(file_name) as infile, open(file_name+".out","w") as outfile:
	    for i,line in enumerate(infile):
	        if "HERE_"+pattern in line:
	        	outfile.write("/* BEGIN_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")

	        	outfile.write("CPPUNIT_TEST_SUITE( "+"Test_Requests"+" );")
	        	prev_name = "-1"
	        	for m in methods:
	        		if m.gen_test(0) != "":
	        			name = m.getName()
	        			if "stream" not in name:
	        				if name == prev_name:
	        					name += "_1"
	        				outfile.write("\nCPPUNIT_TEST( "+name+"_test"+" );")
			        		prev_name = name


    			outfile.write("CPPUNIT_TEST_SUITE_END();")
    			outfile.write("\n\npublic:\n")

	        	for m in methods:
	        		name = m.getName()
	        		if name == prev_name:
	        			outfile.write( m.gen_test(1) )
	        		else:
	        			outfile.write( m.gen_test(0) )
	        		prev_name = name

	        	outfile.write("\n")
	        	outfile.write("/* END_"+pattern+" don't remove this comment ("+str(t.year)+"/"+str(t.month)+"/"+str(t.day)+" "+str(t.hour)+":"+str(t.minute)+") */\n")
	        else:
	        	outfile.write(line)
	shutil.move(file_name+".out",file_name)



def dump_if_exists(file_name):
	if is_file_exists(file_name):
		print("Ouput file '" + file_name + "' already exists. Saving old file to '" + file_name + ".old'")
		shutil.copy(file_name, file_name+".old")

if len(sys.argv) < 3 :
	print "Usage : "+sys.argv[0]+" <file_to_parse> <output_file_whithout_ext> [<constants_file>.h]"
	print "--> <output_file> will be auto-completed by \".h/.cpp\" (input) and \".out\" (output)"
	sys.exit(1)

def is_file_exists(filename):
	try:
   		with open(filename) as f: pass
	except IOError as e:
   		return 0

   	return 1



#############
# MAIN PROG #
#############

file_name_in = sys.argv[1]
file_name_out = sys.argv[2]

in_exists = 1
out_h_exists = 1


if not is_file_exists(file_name_in):
	print(file_name_in + " : file not found") 
	sys.exit(1)

dump_if_exists(file_name_out+".cpp")
dump_if_exists(file_name_out+".h")


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

print("[ "+str(len(methods))+" methods generated ]")

if len(sys.argv) > 3:
	consts_file = sys.argv[3]
	print("Writing constants in file "+consts_file+"...")
	remove_from_file(consts_file,pattern)
	dump_if_exists(consts_file)
	write_constants_file(consts_file,cm)
	print("Done.")

if len(sys.argv) > 4:
	tests_file = sys.argv[4]
	print("Writing tests in file "+tests_file+"...")
	remove_from_file(tests_file,pattern)
	dump_if_exists(tests_file)
	write_test_suite(tests_file,methods,pattern)
	print("Done.")

#constants_file = open("TwitterConstants.h.out")
# twc.addConst("statuses/mention_timeline")
# twc.addConst("twits/truc_chouette")
#print( cm.gen_space() )
