#include "xpMatrix.h"
#include <iostream>
#include "xpException.h"



void main()
{     
   xpMatrix tmp_1(4);
   xpMatrix tmp_2(4);

   tmp_1.initRandom(23);

   tmp_2.setValueAt(0, 0, 1);
   tmp_2.setValueAt(0, 1, 3);
   tmp_2.setValueAt(0, 2, -1);
   tmp_2.setValueAt(0, 3, 4);
   tmp_2.setValueAt(1, 0, 0);
   tmp_2.setValueAt(1, 1, 2);
   tmp_2.setValueAt(1, 2, 3);
   tmp_2.setValueAt(1, 3, -6);
   tmp_2.setValueAt(2, 0, 7);
   tmp_2.setValueAt(2, 1, -0.5);
   tmp_2.setValueAt(2, 2, -0.8);
   tmp_2.setValueAt(2, 3, 2);
   tmp_2.setValueAt(3, 0, 1);
   tmp_2.setValueAt(3, 1, 4);
   tmp_2.setValueAt(3, 2, -2);
   tmp_2.setValueAt(3, 3, 2.5);

   std::cout << "The first matrix is:" << '\n';
   tmp_1.printMtx();
   std::cout << '\n';

   std::cout << "The second matrix is:" << '\n';
   tmp_2.printMtx();
   std::cout << '\n';

   unsigned int row = 0;
   unsigned int col = 0;

   std::cout << "\n";

   xpMatrix prod;
   xpMatrix add;
   xpMatrix subtract;
   xpMatrix getBack;
   xpMatrix getBack_2;
   xpMatrix invMtx;
	//try
	//{
       prod = tmp_1 * tmp_2;
	   add = tmp_1 + tmp_2;
	   subtract = tmp_1 - tmp_2;
	   invMtx = tmp_2.getInverse();
       getBack = tmp_2 * invMtx;

	   getBack_2 = tmp_2 * invMtx;
	   getBack_2.setNumberOfDecimals(6);

 //   }
	//catch(exception_code ex)
	//{		
	//	printf("Caught an exception");
	//}

    invMtx.SaveFile("Tomas.mtx");
	invMtx.LoadFile("Tomas.mtx");

	std::cout << "The product is:" << '\n';
    prod.printMtx();
	std::cout << '\n';

	std::cout << "The sum is:" << '\n';
    add.printMtx();
	std::cout << '\n';

	std::cout << "The difference is:" << '\n';
    subtract.printMtx();
	std::cout << '\n';

	std::cout << "The inverse matrix is:" << '\n';
	invMtx.printMtx();
	std::cout << '\n';

	std::cout << "The first read back matrix is:" << '\n';
    getBack.printMtx();
	std::cout << '\n';

	std::cout << "The second read back matrix is:" << '\n';
    getBack_2.printMtx();
	std::cout << '\n';


	std::cout << "All Done!";

}


