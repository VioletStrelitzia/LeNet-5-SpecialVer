#include "FileLib.h"
namespace yuki {
	namespace file {
		// ��ȡ�ļ���׺��
		string GetExta(string const& filename)
		{
			auto found = filename.rfind('.');
			string exta;
			if (found != string::npos) {
				exta = filename.substr(found, filename.size() - found);
			} else {
				throw "ERROR: '.' is missing | in string GetExta(string const& filename)\n";
			}
			return exta;
		}
	}

}