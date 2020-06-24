//#include "q5solution.hpp"
//#include "ics46goody.hpp"
//
//int main() {
//  try {
//    //Test maximum
//    std::cout << "Testing maximum" << std::endl;
//    NTN<int> temp;
//
//    //Builds a tree with two children each having 3 children (see print_NTN_tree result)
//    int load1[] = {8,0};
//    int at = 0;
//    temp = build_NTN_tree(load1,at);
//    std::cout << std::endl << "Tree is" << std::endl;
//    print_NTN_tree(temp,"");
//    std::cout << "Maximum in Tree: " << maximum(temp) << std::endl;
//
//    int load2[] = {1,2,5,3,6,0,4,0,2,0,7,3,4,0,10,0,3,0};
//    at = 0;
//    temp = build_NTN_tree(load2,at);
//    std::cout << std::endl << "Tree is" << std::endl;
//    print_NTN_tree(temp,"");
//    std::cout << "Maximum in Tree: " << maximum(temp) << std::endl;
//
//    int load3[] = {1,2,12,3,6,0,4,0,2,0,7,3,4,0,6,0,3,0};
//    at = 0;
//    temp = build_NTN_tree(load3,at);
//    std::cout << std::endl << "Tree is" << std::endl;
//    print_NTN_tree(temp,"");
//    std::cout << "Maximum in Tree: " << maximum(temp) << std::endl << std::endl;
//
//    //Uncomment the statement below to enter another tree by hand: a bit tedious
//    //temp = build_NTN_tree("","root");
//
//
//    //Test longest_word
//    //Preload with the words (enter others as prompted)
//    DTN root1_DTN;
//    std::cout << std::endl << "Testing longest_word" << std::endl;
//    std::cout << "adding ante" << std::endl;
//    add_a_word(root1_DTN,"ante");
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//    std::cout << "adding anteater" << std::endl;
//    add_a_word(root1_DTN,"anteater");
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//    std::cout << "adding anthem" << std::endl;
//    add_a_word(root1_DTN,"anthem");
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//    std::cout << "adding anthebellum" << std::endl;
//    add_a_word(root1_DTN,"antebellum");
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//    std::cout << "adding anteatersforics46" << std::endl;
//    add_a_word(root1_DTN,"aneatersforics46");
//
//    std::cout << "Digital Tree of words (marked with *)" << std::endl;
//    print_DTN_tree(root1_DTN,"");
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//    while (true) {
//      std::string word = ics::prompt_string("Enter word to add (QUIT to quit)");
//      if (word == "QUIT")
//        break;
//      add_a_word(root1_DTN,word);
//    }
//
//    std::cout << "Digital Tree of words (marked with *)" << std::endl;
//    print_DTN_tree(root1_DTN,"");
//
//    std::cout << "longest word = " << longest_word(root1_DTN) << std::endl;
//
//
//    //Test stats
//    std::cout << std::endl << "Testing stats" << std::endl;
//    //Preload with the words (enter others as prompted; then tests dictionary file)
//    DTN root2_DTN;
//    std::cout << std::endl << "adding anteater" << std::endl;
//    add_a_word(root2_DTN,"anteater");
//    std::cout << std::endl << "Tree is" << std::endl;
//    print_DTN_tree(root2_DTN,"");
//    std::cout << "stats = " << stats(root2_DTN) << std::endl;
//
//    std::cout << std::endl << "adding ant" << std::endl;
//    add_a_word(root2_DTN,"ant");
//    std::cout << "Tree is" << std::endl;
//    print_DTN_tree(root2_DTN,"");
//    std::cout << "stats = " << stats(root2_DTN) << std::endl;
//
//    std::cout << std::endl << "adding ante" << std::endl;
//    add_a_word(root2_DTN,"ante");
//    std::cout << "Tree is" << std::endl;
//    print_DTN_tree(root2_DTN,"");
//    std::cout << "stats = " << stats(root2_DTN) << std::endl;
//
//    std::cout << std::endl << "adding anthem" << std::endl;
//    add_a_word(root2_DTN,"anthem");
//    std::cout << "Tree is" << std::endl;
//    print_DTN_tree(root2_DTN,"");
//    std::cout << "stats = " << stats(root2_DTN) << std::endl;
//
//    std::cout << std::endl << "adding animal" << std::endl;
//    add_a_word(root2_DTN,"animal");
//    std::cout << "Tree is" << std::endl;
//    print_DTN_tree(root2_DTN,"");
//    std::cout << "stats = " << stats(root2_DTN) << std::endl;
//
//    std::cout << std::endl << "Add your own words" << std::endl;
//    while (true) {
//      std::string word = ics::prompt_string("Enter new word to add (QUIT to quit)");
//      if (word == "QUIT")
//        break;
//      add_a_word(root2_DTN,word);
//      std::cout << "Tree is" << std::endl;
//      print_DTN_tree(root2_DTN,"");
//      std::cout << "stats = " << stats(root2_DTN) << std::endl;
//    }
//
////    std::cout << "Digital Tree of words (marked with *)" << std::endl;
////    print_DTN_tree(root_DTN,"");
//
//    std::cout << std::endl << "Testing Dictionary of ~ 20K words (dict3.txt takes a few seconds to load)" << std::endl;
//    std::ifstream dict_file;
//    DTN dict;
//    ics::safe_open(dict_file,"Enter file name to read", "dict3.txt");
//    std::string word;
//    while (getline(dict_file,word))
//      add_a_word(dict,word);
//    std::cout << std::endl << "Dictionary Read; Testing stats" << std::endl;
//    ics::pair<int,int> s = stats(dict);
//    std::cout << "stats = " << s << std::endl;
//    std::cout << "density of digital tree = " << double(s.second)/double(s.first) << std::endl;
//
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//  return 0;
//}
//
//
//
///*
//Result from running driver: not Googletest for this code
//
//Testing Testing maximum
//
//Tree is
//8
//Maximum in Tree: 8
//
//Tree is
//1
//  5
//    6
//    4
//    2
//  7
//    4
//    10
//    3
//Maximum in Tree: 10
//
//Tree is
//1
//  12
//    6
//    4
//    2
//  7
//    4
//    6
//    3
//Maximum in Tree: 12
//
//
//Testing longest_word
//adding ante
//longest word = ante
//adding anteater
//longest word = anteater
//adding anthem
//longest word = anteater
//adding anthebellum
//longest word = antebellum
//adding anteatersforics46
//Digital Tree of words (marked with *)
//
//  a
//    an
//      ant
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//          anteb
//            antebe
//              antebel
//                antebell
//                  antebellu
//                    antebellum*
//        anth
//          anthe
//            anthem*
//      ane
//        anea
//          aneat
//            aneate
//              aneater
//                aneaters
//                  aneatersf
//                    aneatersfo
//                      aneatersfor
//                        aneatersfori
//                          aneatersforic
//                            aneatersforics
//                              aneatersforics4
//                                aneatersforics46*
//longest word = aneatersforics46
//Enter word to add (QUIT to quit): smallword
//Enter word to add (QUIT to quit): QUIT
//Digital Tree of words (marked with *)
//
//  a
//    an
//      ant
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//          anteb
//            antebe
//              antebel
//                antebell
//                  antebellu
//                    antebellum*
//        anth
//          anthe
//            anthem*
//      ane
//        anea
//          aneat
//            aneate
//              aneater
//                aneaters
//                  aneatersf
//                    aneatersfo
//                      aneatersfor
//                        aneatersfori
//                          aneatersforic
//                            aneatersforics
//                              aneatersforics4
//                                aneatersforics46*
//  s
//    sm
//      sma
//        smal
//          small
//            smallw
//              smallwo
//                smallwor
//                  smallword*
//longest word = aneatersforics46
//
//Testing stats
//
//adding anteater
//
//Tree is
//
//  a
//    an
//      ant
//        ante
//          antea
//            anteat
//              anteate
//                anteater*
//stats = pair[9,1]
//
//adding ant
//Tree is
//
//  a
//    an
//      ant*
//        ante
//          antea
//            anteat
//              anteate
//                anteater*
//stats = pair[9,2]
//
//adding ante
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//stats = pair[9,3]
//
//adding anthem
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//        anth
//          anthe
//            anthem*
//stats = pair[12,4]
//
//adding animal
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//        anth
//          anthe
//            anthem*
//      ani
//        anim
//          anima
//            animal*
//stats = pair[16,5]
//
//Add your own words
//Enter new word to add (QUIT to quit): farm
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//        anth
//          anthe
//            anthem*
//      ani
//        anim
//          anima
//            animal*
//  f
//    fa
//      far
//        farm*
//stats = pair[20,6]
//Enter new word to add (QUIT to quit): farmer
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//        anth
//          anthe
//            anthem*
//      ani
//        anim
//          anima
//            animal*
//  f
//    fa
//      far
//        farm*
//          farme
//            farmer*
//stats = pair[22,7]
//Enter new word to add (QUIT to quit): faramhand
//Tree is
//
//  a
//    an
//      ant*
//        ante*
//          antea
//            anteat
//              anteate
//                anteater*
//        anth
//          anthe
//            anthem*
//      ani
//        anim
//          anima
//            animal*
//  f
//    fa
//      far
//        farm*
//          farme
//            farmer*
//        fara
//          faram
//            faramh
//              faramha
//                faramhan
//                  faramhand*
//stats = pair[28,8]
//Enter new word to add (QUIT to quit): QUIT
//
//Testing Dictionary of ~ 20K words (dict3.txt takes a few seconds to load)
//Enter file name to read[dict3.txt]:
//
//Dictionary Read; Testing stats
//stats = pair[61616,19911]
//density of digital tree = 0.323147
//
//*/
