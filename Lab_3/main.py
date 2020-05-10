def getStateTransitionsFromFile():
    i = 0
    f = open("input")
    n = int(f.readline())
    transitions = []
    for i in range(n):
        str = f.readline()
        left = str[:str.index(" ")]
        right = str[str.index(" ") + 1:]
        right = right.replace("\n", "")
        transitions.append([left, right])
    return transitions


def verifyStartElement():
    for item in states:
        if item[1].find('S'):
            print("Found")
            vec = ["1","2"]
            vec[0] = "S0"
            vec[1] = "S"
            states.append(vec)
            break
    return states

def verifyForNullStatement():

    elementWithNull = ""
    ind = 0
    for item in states:
        if item[1] == "0":
            elementWithNull = item[0][0]
            itemToDelete = item
            states.remove(item)
            break
        ind += 1
    for item in states:

        if elementWithNull in item[1]:
            newString = item[1]
            newString = newString.replace(elementWithNull, "")
            item.append(newString)
    return states

def removeUnitProduction():
    for item in states:
        index = 1
        while index < len(item):
            # print(index)
            elementFromTheRightSide = item[index]
            # print(elementFromTheRightSide[0])
            if len(elementFromTheRightSide) == 1 and ord(elementFromTheRightSide) >= 65 and ord(elementFromTheRightSide) <= 90:
                for item1 in states:
                    if(elementFromTheRightSide == item1[0]):
                        index1 = 1
                        while index1 < len(item1):
                            if(item1[index1] not in item):
                                item.append(item1[index1])
                            index1 += 1
                        item.remove(item[index])
                        # print(item1)
            index += 1


states = getStateTransitionsFromFile()
states = verifyStartElement()
states = verifyForNullStatement()
removeUnitProduction()
print(states)