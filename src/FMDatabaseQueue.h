//
//  FMDatabasePool.h
//  fmdb
//
//  Created by August Mueller on 6/22/11.
//  Copyright 2011 Flying Meat Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "sqlite3.h"

@class FMDatabase;

@interface FMDatabaseQueue : NSObject {
    NSString            *_path;
    NSString            *_attachedDBAlias;
    dispatch_queue_t    _queue;
    FMDatabase          *_db;
}

@property (atomic, retain) NSString *path;
@property (atomic, retain) NSString *attachedDBAlias;


+ (id)databaseQueueWithPath:(NSString*)aPath;
+ (id)databaseQueueWithPath:(NSString*)aPath attachedToDBAtPath:(NSString*)bPath as:(NSString *)alias;
- (id)initWithPath:(NSString*)aPath;
- (id)initWithPath:(NSString *)aPath attachedToDBAtPath:(NSString *)bPath as:(NSString *)alias;
- (void)close;

- (void)inDatabase:(void (^)(FMDatabase *db))block;

- (void)inTransaction:(void (^)(FMDatabase *db, BOOL *rollback))block;
- (void)inDeferredTransaction:(void (^)(FMDatabase *db, BOOL *rollback))block;

#if SQLITE_VERSION_NUMBER >= 3007000
// NOTE: you can not nest these, since calling it will pull another database out of the pool and you'll get a deadlock.
// If you need to nest, use FMDatabase's startSavePointWithName:error: instead.
- (NSError*)inSavePoint:(void (^)(FMDatabase *db, BOOL *rollback))block;
#endif

@end

