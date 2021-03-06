#include "stdafx.h"
#include "CppUnitTest.h"
#include "AutomateFileParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUnitaires
{		
	TEST_CLASS(AutomateFileParserTests)
	{
	public:
		
		TEST_METHOD(Test_convertStringToArray)
		{
			string s = "4 1 2 -3 6";
			int tabAnswer[4] = {1, 2, -3, 6};
			int tabAnswerSize = 4;

			int * tab;
			int size;

			AutomateFileParser afp;
			afp.convertStringToArray(s, &tab, &size);

			Assert::AreEqual(tabAnswerSize, size);
			for(int i = 0; i < tabAnswerSize; i++)
				Assert::AreEqual(tabAnswer[i], tab[i]);
		}

		TEST_METHOD(Test_convertStringToTransitionData)
		{
			string s = "1a2";
			int from, to;
			char label;

			AutomateFileParser afp;
			afp.convertStringToTransitionData(s, &from, &label, &to);

			Assert::AreEqual(1, from);
			Assert::AreEqual('a', label);
			Assert::AreEqual(2, to);
		}

		TEST_METHOD(Test_generateAlphabet)
		{
			string s = "abcdefghijkl";
			string s2 = "abc";
			string s3 = "";

			AutomateFileParser afp;
			string ret = afp.generateAlphabet(s.length());
			string ret2 = afp.generateAlphabet(s2.length());
			string ret3 = afp.generateAlphabet(s3.length());

			Assert::AreEqual(s, ret);
			Assert::AreEqual(s2, ret2);
			Assert::AreEqual(s3, ret3);
		}

		TEST_METHOD(Test_generate)
		{
			AutomateFileParser afp;
			afp.setDebugged(true);
			afp.loadFile("../automate_tests.txt");
			Automate a = *afp.generate();

			Assert::AreEqual(2, (int)a.alphabet.length());
			Assert::AreEqual(3, (int)a.etats.size());
			Assert::AreEqual(1, (int)a.entrees.size());
			Assert::AreEqual(2, (int)a.sorties.size());
			Assert::AreEqual(4, (int)a.transitions.size());
		}
	};

	TEST_CLASS(AutomateTests)
	{
		TEST_METHOD(Test_estComplet)
		{
			try
			{
				AutomateFileParser afp;
				afp.loadFile("../automate_complet1.txt");

				Automate complet = *afp.generate();
				Assert::IsTrue(complet.estComplet());

				afp.loadFile("../automate_presque_complet1.txt");

				Automate presque = *afp.generate();
				Assert::IsFalse(presque.estComplet());

				afp.loadFile("../automate_tests.txt");

				Automate nope = *afp.generate();
				Assert::IsFalse(nope.estComplet());
			}
			catch(exception& e)
			{
				cout << "[EXCEPTION] " << e.what() << endl;
				Assert::Fail();
			}
		}

		TEST_METHOD(PerfTest_estComplet_cached_100000it)
		{
			try
			{
				AutomateFileParser afp;
				afp.loadFile("../automate_presque_complet1.txt");

				Automate presque = *afp.generate();
				presque.setCached(true);

				for(int i = 0; i < 50000; i++)
					Assert::IsFalse(presque.estComplet());

				//On le complete
				presque.ajouterTransition(2, 'b', 2);

				for(int i = 0; i < 50000; i++)
					Assert::IsTrue(presque.estComplet());

			}
			catch(exception& e)
			{
				cout << "[EXCEPTION] " << e.what() << endl;
				Assert::Fail();
			}
		}

		TEST_METHOD(PerfTest_estComplet_uncached_100000it)
		{
			try
			{
				AutomateFileParser afp;
				afp.loadFile("../automate_presque_complet1.txt");

				Automate presque = *afp.generate();
				presque.setCached(false);

				for(int i = 0; i < 50000; i++)
					Assert::IsFalse(presque.estComplet());

				//On le complete
				presque.ajouterTransition(2, 'b', 2);

				for(int i = 0; i < 50000; i++)
					Assert::IsTrue(presque.estComplet());

			}
			catch(exception& e)
			{
				cout << "[EXCEPTION] " << e.what() << endl;
				Assert::Fail();
			}
		}
	};
}