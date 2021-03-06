/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
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
#include "MemoryCachedStorage.h"
#include "ChunkStorage.h"

namespace librevault {

MemoryCachedStorage::MemoryCachedStorage(QObject* parent) : QObject(parent), cache_(50*1024*1024) {}    // 50 MB cache is enough for most purposes

bool MemoryCachedStorage::have_chunk(const blob& ct_hash) const noexcept {
	return cache_.contains(conv_bytearray(ct_hash));
}

QByteArray MemoryCachedStorage::get_chunk(const blob& ct_hash) const {
	QMutexLocker lk(&cache_lock_);

	QByteArray* cached_chunk = cache_[conv_bytearray(ct_hash)];
	if(cached_chunk)
		return *cached_chunk;
	else
		throw ChunkStorage::no_such_chunk();
}

void MemoryCachedStorage::put_chunk(const blob& ct_hash, QByteArray data) {
	QMutexLocker lk(&cache_lock_);

	QByteArray* cached_chunk = new QByteArray(data);
	cache_.insert(conv_bytearray(ct_hash), cached_chunk, cached_chunk->size());
}

void MemoryCachedStorage::remove_chunk(const blob& ct_hash) noexcept {
	QMutexLocker lk(&cache_lock_);

	cache_.remove(conv_bytearray(ct_hash));
}

} /* namespace librevault */
