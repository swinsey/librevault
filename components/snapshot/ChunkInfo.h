/* Copyright (C) 2017 Alexander Shishenko <alex@shishenko.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#pragma once
#include "EncryptedData.h"
#include <Secret.h>
#include <QByteArray>
#include <QSharedData>
#include <chrono>

namespace librevault {

namespace serialization {
class Inode_ChunkInfo;
}

class ChunkInfo {
	struct ChunkInfoData : public QSharedData {
		QByteArray ct_hash;
		quint32 size;
		QByteArray iv;

		QByteArray pt_keyed_hash;
	};

public:
	ChunkInfo() {d = new ChunkInfoData;}
	ChunkInfo(const serialization::Inode_ChunkInfo& serialized);
	operator serialization::Inode_ChunkInfo() const;

	QByteArray ctHash() const {return d->ct_hash;}
	void setCtHash(QByteArray ct_hash) {d->ct_hash = ct_hash;}

	quint32 size() const {return d->size;}
	void setSize(quint32 size) {d->size = size;}

	QByteArray iv() const {return d->iv;}
	void setIv(QByteArray iv) {d->iv = iv;}

	QByteArray ptKeyedHash() const {return d->pt_keyed_hash;}
	void setPtKeyedHash(QByteArray pt_keyed_hash) {d->pt_keyed_hash = pt_keyed_hash;}

private:
	QSharedDataPointer<ChunkInfoData> d;
};

} /* namespace librevault */