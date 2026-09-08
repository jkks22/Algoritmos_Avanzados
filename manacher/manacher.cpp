//Mancher pseudo code 
/*  
function (main string):
    max counter = 0
    L = array[] 
    lenght of main string
    new string = $ + i of main string + $
    vairiable pointer = 0
    mirror = pointer - 1
    for i = 1 to length of new string - 1:
        if mirror = i:
            counter++
            mirror--
            i++
            else:
            L.push(counter)
            if counter > max counter:
                max counter = counter
                start = techo( (maxIndex - maxLen) / 2 )
                end   = start + maxLen - 1
                new array = main string[start:end]
            pointer++
            mirror = pointer - 1
            i = pointer + 1
    return L
    return new array

    */