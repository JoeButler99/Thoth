#!/usr/bin/env python
import sys
import optparse
import pydot
import matplotlib.pyplot as plt
import Image

guesses_filename = "program_guesses"
nodetree_filename = "nodetree.0"

# CLI Parser
valid_actions = ['plotResultsLine','plotTargetsLine','plotAllLines','plotResultsPoints','plotTargetsPoints','plotAllPoints','functionsBarChart','terminalsBarChart','depthBarChart','nodetreeGraphviz']
parser = optparse.OptionParser(description="Thoth Graphing Tools")
parser.add_option("-a","--action",action="store",dest="action",help="Which action to perform. Valid choices are %s"%valid_actions,choices=valid_actions)
parser.add_option("-g","--guesses-file", action="store",dest="guesses_file", type=str,help="What program guesses file to load. Default is %s" % guesses_filename,default=guesses_filename)
parser.add_option("-n","--nodetree-file",action="store",dest="nodetree_file",type=str,help="Which nodetree file to load. Default is %s" % nodetree_filename,default=nodetree_filename)
(options, args) = parser.parse_args()

if not options.action:
    parser.print_help()
    parser.error("No action specified")

# Check some of the optional settings
if not options.guesses_file:
    options.guesses_file = guesses_filename
if not options.nodetree_file:
    options.nodetree_file = nodetree_filename


# ProgramGuesses interacts with the 'program_guesses' file which can be produced by Thoth
class ProgramGuesses:
    def __init__(self):
        self.loaded = False
        self.labels  = []
        self.targets = []
        self.results = []
    
    # Clean up the result line and add the data
    def add_line(self,line):
        try:
            cleaned = line.strip().replace("Case: ",'').replace("Target: ",'').replace("Result: ",'')
            case, target, result = cleaned.split()
            self.labels.append(int(case))
            self.targets.append(float(target))
            self.results.append(float(result))
        except:
            print "ERROR PARSING: %s" % line
            sys.exit(2)
    
    # Load the program guesses file into the class
    def load_file(self):
        try:
            with open(options.guesses_file,'r') as f:
                for line in f:
                    if len(line) > 0 and line[0] != '#':
                        self.add_line(line)
            self.loaded = True
        except:
            print "Error loading %s" % guesses_filename
            sys.exit(1)

    def print_all(self):
        print self.labels
        print self.targets
        print self.results
    
    def get_targets_array(self):
        if not self.loaded:
            self.load_file()
        return self.targets
        
    def get_results_array(self):
        if not self.loaded:
            self.load_file()
        return self.results

# Nodetree interacts with the nodefile structures produced by Thoth
class Nodetree:
    def __init__(self):
        self.loaded = False
        self.function_map   = {}
        self.terminal_map   = {}
        self.depth_map      = {}
        self.generated_from = ""
        self.tree_score     = 0.0
        self.total_nodes    = 0
        self.constants      = []
        self.outputs        = 0
        
    def get_node(self,line):
        depth = 0
        while line[0] == '.':
            depth += 1
            line = line[1:]
        if depth not in self.depth_map.keys():
            self.depth_map[depth] = 1
        else: 
            self.depth_map[depth] += 1
        
        if line[0] == "T":
            is_terminal = True
            name = int(line.replace("T:",'').replace("|",''))
        else:
            is_terminal = False
            name = line.split("|")[1].strip()
            
        return depth , name , is_terminal
        
    def add_node(self,line):
        depth , name , is_terminal = self.get_node(line)
            
        if is_terminal:
            if name not in self.terminal_map.keys():
                self.terminal_map[name] = 1
            else:
                self.terminal_map[name] += 1
        else:
            if name not in self.function_map.keys():
                self.function_map[name] = 1
            else:
                self.function_map[name] += 1

        
    def add_line(self,line):
        try:
            cleaned = line.strip()
            # Get the stats headers
            if cleaned[0] == '#':
                if 'Generated Node Tree from' in cleaned:
                    self.generated_from = cleaned.replace("# Generated Node Tree from ",'')
                if 'This Tree scored:' in cleaned:
                    self.tree_score = float(cleaned.replace("# This Tree scored: ",''))
                if 'Total Nodes' in cleaned:
                    self.total_nodes = int(cleaned.replace('# Total Nodes: ',''))
            # Load the array of constants
            if 'CONSTANTS ' in cleaned:
                self.constants = [ float(x) for x in cleaned.replace('CONSTANTS ','').rstrip('|').lstrip("+").split('+') ]
            # Load the nodes and their depths
            if cleaned[0] == 'F' and cleaned[1] != 'U' and cleaned[2] != '-':
                self.outputs = int(cleaned.replace('F:-1| ROOT WITH(','').replace(') inputs',''))
                self.function_map['Root (%s)' % str(self.outputs)] = 1 
            if cleaned[0] == '.':
                self.add_node(cleaned)
        except:
            print "ERROR PARSING: %s" % line
            sys.exit(2)
        
    def load_file(self):
        try:
            with open(options.nodetree_file,'r') as f:
                for line in f:
                    if len(line) > 0:
                        self.add_line(line)
            self.loaded = True
        except:
            print "Error loading %s" % nodetree_filename
            sys.exit(1)
    
    def get_data_label_arrays(self,mapname):
        if not self.loaded:
            self.load_file()
        data   = []
        labels = []
        for k , v in sorted(mapname.items()):
            data.append(v)
            labels.append(k)             
        return data, labels        

# PyDot aims to draw the nodetree in the GraphViz dot language
class PyDot:
    def __init__(self):
        self.loaded   = False
        self.parents  = {}
        self.graph    = None
        self.nt       = Nodetree()
        self.node_no  = 0
        self.t_colour = "#e6c5c5"
        self.f_colour = "#b8d6f3"
        
    def add_node(self,line):
        cleaned = line.strip()
        depth , name , is_terminal = nt.get_node(line)
        if cleaned[0] == 'F' and cleaned[1] != 'U':
            n = pydot.Node(self.node_no, label=name,style="filled",fillcolor="green")
            self.parents[0] = n
            self.graph.add_node(n)
        else:
            # If we are not the root node, we need to connect to the parent
            if is_terminal:
                name = "T " + str(name)
                colour = self.t_colour
            else:
                colour = self.f_colour
            n = pydot.Node(self.node_no, label=name,style="filled",fillcolor=colour)
            self.parents[depth] = n
            self.graph.add_node(n)
            self.graph.add_edge(pydot.Edge(self.parents[depth -1],n))
        self.node_no += 1
        
    def load_file(self):
        try:
            with open(options.nodetree_file,'r') as f:
                for line in f:
                    if len(line) > 0 and line[0] != '#' and line[0] != "C":
                        self.add_node(line)
            self.loaded = True
        except:
            print "Error loading %s" % nodetree_filename
            print "Unexpected error:", sys.exc_info()[0]
            sys.exit(1)
            
    
    def display(self):
        f = Image.open('nodetree.png').show()
            
    def draw(self,graphname,display=True):
        self.graph = pydot.Dot("MER",graph_type='graph')
        self.load_file()
        self.graph.write_png('nodetree.png')
        if display:
            self.display()
    
# Plotter takes the data and produces a graph for the user         
class Plotter:
    def set_attr(self,title,x_label,y_label):
        plt.title(title)
        plt.xlabel(x_label)
        plt.ylabel(y_label)
        
    def wait(self):
        raw_input('Please press return to continue...\n')
    
    def plot_line(self,data,title,y_label,x_label="Case No"):
        plt.plot(data)
        self.set_attr(title, x_label, y_label)
        plt.show()
 
    def plot_points(self,data,title,y_label,x_label="Case No"):
        plt.plot(data,'rx',linewidth=0.5)
        self.set_attr(title, x_label, y_label)
        plt.show()
        
        
    def plot_multi_points(self,datas,labels,title,y_label,x_label="Case No"):
        self.set_attr(title, x_label, y_label)
        for d in datas:
            plt.plot(d,'x')
        plt.legend(labels)
        plt.show()
        
    def plot_multi_lines(self,datas,labels,title,y_label,x_label="Case No"):
        self.set_attr(title, x_label, y_label)
        for d in datas:
            plt.plot(d)
        plt.legend(labels)
        plt.show()
        
    def draw_bar_chart(self,data,title,y_label,x_label="Name",x_small_labels=None):
        plt.bar(range(len(data)), data, align='center')
        plt.xticks(range(len(data)),x_small_labels , size='small',rotation=70)
        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.title(title)
        plt.show()


        
#       
# Main
# 
pg      = ProgramGuesses()
nt      = Nodetree()
plotter = Plotter()
pd      = PyDot()
if options.action == 'plotResultsLine':
    plotter.plot_line(pg.get_results_array(), "Program Results Graph", "Result")
if options.action == 'plotTargetsLine':
    plotter.plot_line(pg.get_targets_array(), "Program Targets Graph", "Result")
elif options.action == 'plotResultsPoints':
    plotter.plot_points(pg.get_results_array(), "Program Results Points", 'Program Result')
elif options.action == 'plotTargetsPoints':
    plotter.plot_points(pg.get_targets_array(), "Program Targets Points", 'Program Target')    
elif options.action == 'plotAllPoints':
    points = [pg.get_results_array(),pg.get_targets_array()]
    labels = ['results','targets'] 
    plotter.plot_multi_points(points,labels,"Program Targets and Results Points", 'Target / Result')
    
elif options.action == 'plotAllLines':
    points = [pg.get_results_array(),pg.get_targets_array()]
    labels = ['results','targets'] 
    plotter.plot_multi_lines(points,labels,"Program Targets and Results Lines", 'Target / Result')
    
elif options.action == 'functionsBarChart':
    nt.load_file()
    data , labels = nt.get_data_label_arrays(nt.function_map)
    plotter.draw_bar_chart(data, "Function Use", "Count",x_label="Function Name",x_small_labels=labels)

elif options.action == 'terminalsBarChart':
    nt.load_file()
    data , labels = nt.get_data_label_arrays(nt.terminal_map)
    plotter.draw_bar_chart(data, "Terminal Use", "Count",x_label="Terminal Number",x_small_labels=labels)
    
elif options.action == 'depthBarChart':
    data , labels = nt.get_data_label_arrays(nt.depth_map)
    plotter.draw_bar_chart(data, "Depth Chart", "Distance from Root",x_label="Tree Depth",x_small_labels=labels)
elif options.action == 'nodetreeGraphviz':
    pd.draw("Node Tree")
