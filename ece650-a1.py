#!/usr/bin/env python3
import sys
import math
import re

#Final Program
def convertToTuples(ipvals):
    value_list = []
    error_code = 0

    for i in ipvals:
        splitVal = i.split(',')

        a = int(splitVal[0][splitVal[0].index('(') + 1:])
        b = int(splitVal[1][:splitVal[1].index(')')])
        if (a, b) in value_list:
            return error_code

        value_list.append((a, b))
    return value_list


# global variables to store info across program

graph = dict()
setVertex = set()
ll = dict()
line_segments = {}
vertex = dict()


def create_line_segments():
    global line_segments, ll, vertex, setVertex
    setVertex = set()
    ll = dict()
    line_segments = {}
    vertex = dict()
    for i in graph.keys():
        line_segments[i] = []
        for j in range(len(graph[i]) - 1):
            line_segments[i].append((graph[i][j], graph[i][j + 1]))


def distance(A, B):
    return math.sqrt((A[0] - B[0]) ** 2 + (A[1] - B[1]) ** 2)


def line_intersection(line1, line2):
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    l1x1 = line1[0][0]
    l1x2 = line1[1][0]
    l1y1 = line1[0][1]
    l1y2 = line1[1][1]
    l2x1 = line2[0][0]
    l2x2 = line2[1][0]
    l2y1 = line2[0][1]
    l2y2 = line2[1][1]

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div != 0:
        d = (det(*line1), det(*line2))
        x = det(d, xdiff) / div
        y = det(d, ydiff) / div
        l1length = distance((l1x1, l1y1), (l1x2, l1y2))
        l2length = distance((l2x1, l2y1), (l2x2, l2y2))

        if distance((x, y), (l1x1, l1y1)) > l1length or distance((x, y), (l1x2, l1y2)) > l1length or \
                distance((x, y), (l2x1, l2y1)) > l2length or distance((x, y), (l2x2, l2y2)) > l2length:
            return

        return x, y


def compute_vertices():
    road_names = list(graph.keys())
    for i in range(len(road_names) - 1):
        for j in range(i + 1, len(road_names)):
            for k in line_segments[road_names[i]]:
                for l in line_segments[road_names[j]]:
                    iPoint = line_intersection(k, l)

                    if iPoint:
                        # print(k, ' And ', l, ' = ', iPoint)
                        setVertex.add(k[0])
                        setVertex.add(k[1])
                        setVertex.add(l[0])
                        setVertex.add(l[1])
                        setVertex.add(iPoint)

                        if k not in ll:
                            ll[k] = []
                        if l not in ll:
                            ll[l] = []
                        if iPoint not in ll[k] and iPoint not in k:
                            ll[k].append(iPoint)
                        if iPoint not in ll[l] and iPoint not in l:
                            ll[l].append(iPoint)


def set_vertex_to_dict():
    global setVertex, vertex
    counter = 0
    for i in setVertex:
        vertex[counter] = i
        counter += 1


def compute_edges():
    edges = set()
    newEdges = []

    for i in ll.keys():
        newEdges.append([])
        newEdges[-1].append(i[0])
        newEdges[-1] += ll[i]
        newEdges[-1].append(i[1])
        newEdges[-1] = sorted(newEdges[-1], key=lambda k: (k[0],k[1]))

    vertexList = list(vertex.values())

    # print(newEdges)
    for i in newEdges:
        for j in range(len(i) - 1):
            a = vertexList.index(i[j]) + 1
            b = vertexList.index(i[j + 1]) + 1

            edges.add('<' + str(a) + ',' + str(b) + '>')


    vertexOutput = 'V = {'
    for i in vertex.keys():

        a = "{0:.2f}".format(vertex[i][0])
        b = "{0:.2f}".format(vertex[i][1])
        if int(vertex[i][0]) == vertex[i][0]:
            a = int(vertex[i][0])
        if int(vertex[i][1]) == vertex[i][1]:
            b = int(vertex[i][1])

        vertexOutput += '\n' + str(i) + ': ' + '(' + str(a) + ',' + str(b) +')'
    vertexOutput += '\n' + '}'

    listOfEdges = [i.replace(' ','') for i in edges]
    edgesOutput = 'E {'


    for i in range(len(listOfEdges)):
        edgesOutput += listOfEdges[i]

        if i < len(listOfEdges)-1:
            edgesOutput += ','

    edgesOutput +=  '}'

    # vString = "V " + str(len(vertexList))
    print(vertexOutput)
    print(edgesOutput)
#    print(vString)
#    print(edgesOutput)
#     print(vString, end="\n",file=sys.stdout, flush = True)
#     print(edgesOutput,end='\n',file=sys.stdout,  flush = True)
#
    #sys.stdout.write(vString+"\n"+edgesOutput+"\n")
    #sys.stdout.flush()
#
#    # print(vertexOutput)
#    sys.stdout.write(edgesOutput)



def exists_or_not(streetName):
    if streetName.lower() in list(map(str.lower, graph.keys())):
        return True
    return False


def modify(streetName, values):
    for i in graph.keys():
        if i.lower() == streetName.lower():
            graph[i] = values
            break


def remove(streetName):
    for i in graph.keys():
        if i.lower() == streetName.lower():
            del graph[i]
            break


def main():
    while True:
        line = sys.stdin.readline()
        if line == "":
            break
        tupleRegex = r'\((0+|\-?0*[1-9]\d*)\,(0+|\-?0*[1-9]\d*)\)'

        command_re_add = r'(add|mod)\s\"([A-Za-z]+)(\s[A-Za-z]+)*\"(\s\((0+|\-?0*[1-9]\d*)\,(0+|\-?0*[1-9]\d*)\)){2,}$'

        ans = bool(re.match(command_re_add, line))


        if ans:

            values = re.findall(r'\(\-?\d+\,-?\d+\)', line)
            street_name = re.search(r'\"([A-Za-z]+)(\s[A-Za-z]+)*\"', line).group(0)[1: -1:]

            if re.match(r'add', line):
                if exists_or_not(street_name):
                    print('Error - Street Already Exists')
                else:
                    tupleValues = convertToTuples(values)
                    if tupleValues == 0:
                        print('Error - Duplicate Cordinates not Allowed')
                    else:
                        graph[street_name] = tupleValues

            elif re.match(r'mod', line):

                if not exists_or_not(street_name):
                    print('Error - Street Do Not Exist')
                else:
                    tupleValues = convertToTuples(values)
                    if tupleValues == 1:
                        print('Error - Duplicate Cordinates not Allowed')
                    else:
                        modify(street_name, tupleValues)


        elif re.match(r'rm\s\"([A-Za-z]+)(\s[A-Za-z]+)*\"$', line):

            street_name = re.search(r'\"([A-Za-z]+)(\s[A-Za-z]+)*\"', line).group(0)[1: -1:]

            if not exists_or_not(street_name):
                print("Error - Street Do Not Exist")
            else:
                remove(street_name)


        elif re.match(r'gg$', line):

            create_line_segments()
            compute_vertices()
            set_vertex_to_dict()
            compute_edges()

        else:
            print('Error - Invalid Input')



    sys.exit(0)


if __name__ == "__main__":
    main()


