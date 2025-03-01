#include "Sequencer.h"

Sequencer::Sequencer(string fileName){
  // Name: Sequencer (constructor)
  // Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
  //       multiples of three nucleotides
  // Preconditions:  Populates m_fileName from passed information from call
  //                 For example: ./proj3 proj3_data1.txt
  // Postconditions: A sequencer created to populate DNA/mRNA strands

  m_fileName = fileName;
}
 
Sequencer::~Sequencer(){
  // Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
  // Postconditions: All vectors are cleared of DNA and mRNA strands
  //                 Indicates that the strands have been deallocated

  //iterate through the vector
  //at each element, must traverse through the LL and delete each node
  //every node pointer must point to the nullptr

  for (unsigned int i = 0; i < m_DNA.size(); i++){
    delete m_DNA.at(i);
  }
  cout << "Deleting DNA Strands" << endl;

  for (unsigned int i = 0; i < m_mRNA.size(); i++){
    delete m_mRNA.at(i);
  }
  cout << "Deleting mRNA Strands" << endl;
}
  
void Sequencer::StartSequencing(){
  // Name: StartSequencing
  // Desc: Calls ReadFile and continually calls mainmenu until the user exits
  // Preconditions: m_fileName has been populated
  // Postconditions: m_DNA has been populated (after ReadFile concludes)
  ReadFile();
  MainMenu();
}

  
void Sequencer::DisplayStrands(){
  // Name: DisplayStrands
  // Desc: Displays each strand in both mDNA and mRNA
  //       Displays numbered type (For example, DNA 1) then the name of the strand.
  //       Finally displays the strand with arrows between each nucleotide
  // Preconditions: At least one linked list is in mDNA (may have mRNA)
  // Postconditions: Displays DNA strand from one of the vectors

  //using a for loop to iterate through the DNA vector
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    cout << "DNA " << i + 1 << endl;
    cout << "***" << m_DNA.at(i)->GetName() << "***" << endl;
    cout << *m_DNA.at(i);
  }

  //condition to check if mRNA vector is populated
  if (int(m_mRNA.size()) > 0){
    //using a for loop to iterate through the mRNA vector
    for (unsigned int i = 0; i < m_mRNA.size(); i++){
      cout << "mRNA " << i + 1 << endl;
      cout << "***" << m_mRNA.at(i)->GetName() << "***" << endl;
      cout << *m_mRNA.at(i);
    }
  }

}

void Sequencer::ReadFile(){
  // Name: ReadFile
  // Desc: Reads in a file of DNA strands that has the name on one line then
  //       the sequence on the next
  //       All sequences will be an indeterminate length (always evenly divisible by three though).
  //       There are an indeterminate number of sequences in a file.
  //       Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the m_DNA vector
  // Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in m_DNA

  string name = " "; //stores individial's name
  string sequence = " "; //stores individual's DNA sequence

  ifstream inputStream(m_fileName);
  if (inputStream.is_open()) {
    cout << "Opened file." << endl;
  }

  while (getline(inputStream, name, ',') && getline(inputStream, sequence)){
    Strand *myStrand = new Strand(name); //building a strand 

    //this loop will iterate through the sequence string and
    //insert each nucleotide into the linked list (strand).
    for (unsigned int i = 0; i < sequence.length(); i++){
      if (sequence[i] != '\0' && sequence[i] != ',' && sequence[i] != '\n'){
        myStrand->InsertEnd(sequence[i]);
      }
    }
    m_DNA.push_back(myStrand); //once strands are made, they are inserted into the vector
  }
  cout << int(m_DNA.size()) << " strand(s) loaded." << endl;
  inputStream.close();
}

int Sequencer::MainMenu(){
  // Name:  MainMenu
  // Desc: Displays the main menu and manages exiting.
  //       Returns 5 if the user chooses to quit, else returns 0
  // Preconditions: m_DNA populated
  // Postconditions: Indicates the user has quit the program

  int userChoice = 0; //stores user input for the main menu prompt

  while(userChoice != 5){
    cout << "What would you like to do?: " << endl;
    cout << "1. Display Strands" << endl;
    cout << "2. Reverse Strand" << endl;
    cout << "3. Transcribe DNA to mRNA" << endl;
    cout << "4. Translate mRNA to Amino Acids" << endl;
    cout << "5. Exit" << endl;
    cin >> userChoice;

     switch(userChoice){
      case 1:
        DisplayStrands();
        break;
            
      case 2:
        ReverseSequence();
        break;

      case 3:
        Transcribe();
        break;

      case 4:
        Translate();
        break;

      case 5:
        cout << "Exiting program" << endl;
        break;
    }
  }

  return 0;
}
  
int Sequencer::ChooseDNA(){
  // Name: ChooseDNA
  // Desc: Asks the user to choose one strand to use from loaded DNA strands
  // Preconditions: Populated m_DNA
  // Postconditions: Returns index of chosen strand

  int strandNum; //stores the strand num the user wants to reverse

  //condition for when there is a single DNA strand
  if (int(m_DNA.size()) == 1){
    strandNum = 0;
    return strandNum;
  }

  //condition for when there are multiple DNA strands
  else if (int(m_DNA.size()) > 1){
    cout << "Which strand to work with?" << endl;
    cout << "Choose 1 - " << m_DNA.size() << endl;
    cin >> strandNum;
    return strandNum - 1;
  }

  return 0;
}

int Sequencer::ChooseMRNA(){
  // Name: ChooseMRNA
  // Desc: Asks the user to choose one strand to use from translated mRNA strands
  // Preconditions: Populated m_mRNA
  // Postconditions: Returns index of chosen strand

  int strandNum; //stores the strand num the user wants to reverse

  //condition for when mRNA vector is empty
  if (int(m_mRNA.size()) == 0){
    return -1;
  }

  //condition for when there is a single mRNA strand
  else if (int(m_mRNA.size()) == 1){
    strandNum = 0;  
    return strandNum; //returns index 0 to access first element of the list
  }

  //condition for when there are multiple mRNA strands
  else if (int(m_mRNA.size()) > 1){
    cout << "Which strand to work with?" << endl;
    cout << "Choose 1 - " << m_mRNA.size() << endl;
    cin >> strandNum;
    return strandNum - 1;
  }

  return 0;
}

void Sequencer::ReverseSequence(){
  // Name: ReverseSequence
  // Desc: User chooses to reverse either DNA or mRNA to reverse
  //       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
  //       Calls ReverseStrand on chosen location
  // Preconditions: Populated m_DNA or m_mRNA
  // Postconditions: Reverses a specific strand replacing in place

  int userChoice; //stores user's choice of strand
  int index; //ChooseDNA and ChooseMRNA returns index number to this variable

  cout << "Which type of strand to reverse?" << endl;
  cout << "1. DNA" << endl;
  cout << "2. mRNA" << endl;
  cin >> userChoice;

  //condition for choosing DNA
  if (userChoice == 1){
    index = ChooseDNA();
    m_DNA.at(index)->ReverseSequence();
    cout << "Done reversing DNA " << index + 1 << "'s strand." << endl;
  }

  //condition for choosing mRNA
  else if (userChoice == 2){
    //checks if the mRNA vector is populated with data
    if (int(m_mRNA.size()) > 0){
      index = ChooseMRNA();
      m_mRNA.at(index)->ReverseSequence();
      cout << "Done reversing mRNA " << index + 1 << "'s strand." << endl;
    }
    else{
      cout << "No mRNA to reverse; transcribe first." << endl;
    }
  }
}

void Sequencer::Transcribe(){
  // Name: Transcribe
  // Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
  // A->U, T->A, C->G, G->C (DNA to mRNA)
  // Can be called multiple times (will result in multiple mRNA strands)
  // Puts the transcribed mRNA strand into m_mRNA
  // Note: if this function is called more than once on the same strands of DNA,
  // it will add duplicate strands into m_mRNA!
  // Preconditions: Populated m_DNA
  // Postconditions: Transcribes each strand of m_DNA to m_mRNA

  const char BASE_T = 'T'; //base pair for Adenine
  const char BASE_A = 'A'; //base pair for Thymine
  const char BASE_C = 'C'; //base pair for Guanine
  const char BASE_G = 'G'; //base pair for Cytosine

  char nucleotide; //stores the return char from GetData()

  //looping through each DNA strand
  for (unsigned int i = 0; i < m_DNA.size(); i++){

    //create an mRNA strand object to add into mRNA vector
    Strand *mRNAStrand = new Strand(m_DNA.at(i)->GetName());

    //this loop will traverse through a single strand
    for (int j = 0; j < m_DNA.at(i)->GetSize(); j++){

      //receiving each char at each index
      nucleotide = m_DNA.at(i)->GetData(j);

      if (nucleotide == BASE_T){
        mRNAStrand->InsertEnd('A');
      }

      else if (nucleotide == BASE_A){
        mRNAStrand->InsertEnd('U');
      }

      else if (nucleotide == BASE_C){
        mRNAStrand->InsertEnd('G');
      }

      else if (nucleotide == BASE_G){
        mRNAStrand->InsertEnd('C');
      }
    }
    m_mRNA.push_back(mRNAStrand); //insert the new strand into the mRNA vector
  }
  cout << int(m_DNA.size()) << " strand(s) of DNA successfully transcribed into new mRNA strand(s)" << endl;
}

void Sequencer::Translate(){
  // Name: Translate
  // Desc: Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class
  // Preconditions: Populated m_mRNA
  // Postconditions: Translates a specific strand of mRNA to amino acids

  int index = ChooseMRNA(); //returns the index of specified mRNA strand
  string codon = ""; //stores three nucleotides and passes into Convert()
  string aminoAcid = ""; //stores the final protein that is returned from Convert()

  if (index == -1){
    cout << "No mRNA to translate; transcribe first." << endl;
  }

  else{
    cout << "***" << m_mRNA.at(index)->GetName() << "***" << endl;

    //looping through the single mRNA strand
    for (int i = 0; i < m_mRNA.at(index)->GetSize(); i++){
      //concatenating each char to form the codon
      codon += m_mRNA.at(index)->GetData(i);

      //once three chars have been placed together to form a codon,
      //the codon will then be passed into the Convert function to form the amino acid.
      if (codon.length() == 3){
        aminoAcid = Convert(codon);
        cout << codon << "->" << aminoAcid << endl;
        codon = ""; //codon is reset to an empty string for the next three chars
      }
    }
    cout << "Done translating mRNA " << index + 1 << "'s strand." << endl;
  }

}

string Sequencer::Convert(const string trinucleotide){
  // Name: Convert (Provided)
  // Desc: Converts codon (three nodes) into an amino acid
  // Preconditions: Passed exactly three U, A, G, or C
  // Postconditions: Returns the string name of each amino acid

  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");

  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
	  (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");

  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
	  (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");

  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");

  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");

  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");

  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
	  (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");

  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
	  (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");

  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
	  (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");

  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");

  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
	  (trinucleotide=="UCA")||(trinucleotide=="UCG")||
	  (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");

  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");

  else if((trinucleotide=="UGG"))
    return ("Tryptophan");

  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");

  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");

  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");

  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");

  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");

  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");

  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	  (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");

  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");

  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

